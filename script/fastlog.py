import hashlib
import json
import shutil
import platform
import subprocess
import re
import os
import fcntl
import time

# if files use 'fastlog' module


def use_fastlog(fileContext: str):
    pattern = re.compile(r'STR_BUF_WRITE_STRU')
    result = pattern.findall(fileContext)
    return len(result)


def mkdirs(path):
    if True != os.path.exists(path):
        os.makedirs(path)  # makedirs


def preprocess(srcFile: str, includes: str, macro_def: str = ''):
    cmd_str = 'clang -E '+srcFile + ' ' + \
        includes+macro_def
    ret = subprocess.check_output(cmd_str, shell=True)
    return ret.decode("utf-8")


def first_preprocess(srcFile: str, projPath: str, includes: str, macro_def: str = '') -> int:
    relaPath = os.path.relpath(srcFile, projPath)
    preOutPath = os.path.join(projPath, 'fastlog_out', relaPath+'.i')
    mkdirs(os.path.dirname(preOutPath))

    ret = preprocess(srcFile, includes, macro_def)
    preOutFile = open(preOutPath, mode='w+')
    preOutFile.write(ret)
    preOutFile.close
    return use_fastlog(ret)


def second_preprocess(srcFile: str, projPath: str, includes: str, macro_def: str = '') -> int:
    relaPath = os.path.relpath(srcFile, projPath)
    preOutPath = os.path.join(projPath, 'fastlog_out', relaPath+'.ii.c')
    mkdirs(os.path.dirname(preOutPath))

    ret = preprocess(srcFile, includes, macro_def)
    preOutFile = open(preOutPath, mode='w+')
    preOutFile.write(ret)
    preOutFile.close
    return preOutPath


def file_compile_asm(file, inc_paths, outDir, CC, CFLAGS):
    inc_path = ''
    for i_path in inc_paths:
        inc_path += ' -I '+i_path

    macro_defs = " -D FASTLOG_FILE_ADDR="+str(0)

    (relative_dir, fileName) = os.path.split(file)
    out_file_dir = os.path.join(outDir, 'build/myout', relative_dir)
    mkdirs(out_file_dir)
    out_file = os.path.join(out_file_dir, fileName+'.s')
    if True == os.path.isfile(out_file):
        os.remove(out_file)

    cmd_str = CC+' -S '+CFLAGS+file + inc_path + macro_defs
    # print(cmd_str)
    ret = subprocess.check_output(cmd_str, shell=True)

    shutil.move(fileName+'.s', out_file)

    sys = platform.system()
    if sys == "Windows":
        # print(ret.decode('gbk'))  #
        pass
    else:
        # print(ret)
        pass


def file_compile(srcFile: str, projPath: str, compileCmd: str):
    recordItems = {}
    recordItems = read_record(projPath, 'fastlog.json')
    if not recordItems:
        return compileCmd

    recordItemHash = hashlib.md5(
        (srcFile).encode()).hexdigest()
    if recordItemHash in recordItems:
        recordItem = recordItems[recordItemHash]
        compileCmd += " -D FASTLOG_FILE_ADDR=" + \
            str(recordItem['addr_start']) + \
            " -D USE_FASTLOG= -D PYTHON_SCOPE_PRE="
    return compileCmd


def get_count_lvl(count):
    lvl = [0x40, 0x80, 0x100]
    for i in lvl:
        if count < i:
            return i
    return (count/0x100)*0x100+0x100


def need_malloc_addr(countOld, count):
    lvl = get_count_lvl(count)
    lvlOld = get_count_lvl(countOld)
    lvlChg = lvl-lvlOld
    if (0 < lvlChg) or (-2 >= lvlChg):
        return True
    return False


def malloc_addr(recordItemsOld, recordItems):
    addrsFree = []
    for recordItemHash, recordItem in recordItems.items():
        flag = False
        if recordItemHash in recordItemsOld:
            recordItemOld = recordItemsOld[recordItemHash]
            if (recordItemOld['file'] == recordItem['file']):
                recordItems[recordItemHash]['new_file'] = False
                if need_malloc_addr(recordItemOld['count'], recordItem['count']):
                    recordItems[recordItemHash]['re_alloc'] = True
                flag = True
                break
            else:
                return
        if False == flag:
            recordItems[recordItemHash]['re_alloc'] = False

    [addr, len] = [0, 0]
    for recordItemHash, recordItem in recordItems.items():
        if (False == recordItem['new_file']) and (False == recordItems[recordItemHash]['re_alloc']):
            recordItems[recordItemHash]['addr_start'] = recordItemsOld[recordItemHash]['addr_start']
            recordItems[recordItemHash]['addr_len'] = recordItemsOld[recordItemHash]['addr_len']
            if (addr + len) < recordItems[recordItemHash]['addr_start']:
                addrsFree.append(
                    [addr, recordItems[recordItemHash]['addr_start']-addr-len])
            addr = recordItems[recordItemHash]['addr_start']
            len = recordItems[recordItemHash]['addr_len']
    addrsFree.append([addr+len, 0x10000-(addr + len)])
    # print(addrsFree)

    for recordItemHash, recordItem in recordItems.items():
        if (True == recordItem['new_file']) or (True == recordItem['re_alloc']):
            for (i, (addr, len)) in enumerate(addrsFree):
                lvl = get_count_lvl(recordItem['count'])
                if len >= lvl:
                    recordItems[recordItemHash]['addr_start'] = addr
                    recordItems[recordItemHash]['addr_len'] = get_count_lvl(
                        recordItem['count'])
                    if lvl == len:
                        del addrsFree[i]
                    addrsFree[i][0] = addr+lvl
                    addrsFree[i][1] = len-lvl
                    break
    # print(addrsFree)
    return addrsFree[-1][0]


def get_fastlog_call(file_path, out_file_path, print_items):
    # print(out_file_path)
    cmd_str = "clang -std=gnu17 --target=arm-none-eabi -S -O0 -emit-llvm " + \
        ' -ffreestanding -fno-common -g  -mabi=aapcs   -fno-asynchronous-unwind-tables' + \
        " -fno-pie -fno-pic -fno-strict-overflow  " + \
        '  -ffunction-sections -fdata-sections -specs=nano.specs ' +\
        out_file_path+" -o "+out_file_path+".ll"
    # print(cmd_str)
    ret = subprocess.check_output(cmd_str, shell=True)
    sys = platform.system()
    if sys == "Windows":
        # print(ret.decode('gbk'))  #
        pass
    else:
        # print(ret)
        pass

    file = open(out_file_path, mode='r', encoding='UTF-8', errors='ignore')
    context = file.read()
    file.close()

    local_print_items = {}
    pattern = re.compile(
        r'gen_frame(\d+)\.global_cnt = \(\((\d+)\) \+ \((\d+)\)\)')
    result = pattern.findall(context)
    for (line_num, file_addr, line_addr) in result:
        local_print_items[line_num] = {'addr': int(file_addr)+int(line_addr)}
    # print(local_print_items)

    pattern = re.compile(r'fastlog_str(\d+) = "([^"]+)"')
    result = pattern.findall(context)
    for (line_num, print_str) in result:
        local_print_items[line_num]['str'] = print_str

    file = open(out_file_path+".ll", mode='r',
                encoding='UTF-8', errors='ignore')
    context = file.read()
    file.close()
    pattern = re.compile(
        #
        r'sizeof_stru_member(\d+) = internal global \[10 x i32\] (.+), align 4')
    result = pattern.findall(context)
    if result:
        for (line_num, args) in result:
            if ('zeroinitializer' == args):
                args = [0 for x in range(10)]
            else:
                matchObj = re.match(
                    r'\[i32 (\d), i32 (\d), i32 (\d), i32 (\d), i32 (\d), i32 (\d), i32 (\d), i32 (\d), i32 (\d), i32 (\d)\]', args, re.M | re.I)
                args = [int(matchObj.group(x+1)) for x in range(10)]
            local_print_items[line_num]['args'] = args
    else:
        pattern = re.compile(
            r'sizeof_stru_member(\d+) = internal global (.+), align 4')   #
        result = pattern.findall(context)
        if result:
            for (line_num, args) in result:
                if ('[10 x i32] zeroinitializer' == args):
                    args = [0 for x in range(10)]
                else:
                    matchObj = re.match(
                        r'<[^>]+> <{ (.+) zeroinitializer }>', args, re.M | re.I)
                    pattern = re.compile(
                        r'i32 (\d+)')   #
                    result = pattern.findall(matchObj.group(1))
                    args = [0 for x in range(10)]
                    for i in range(0, len(result)):
                        args[i] = result[i]
                    for j in range(i+1, 10):
                        args[j] = '0'

                local_print_items[line_num]['args'] = args

    pattern = re.compile(
        r'typeof_stru_member(\d+) = internal global \[10 x i32\] (.+), align 4')
    result = pattern.findall(context)
    if result:
        for (line_num, args) in result:
            if ('zeroinitializer' == args):
                args = [0 for x in range(10)]
            else:
                matchObj = re.match(
                    r'\[i32 (\d+), i32 (\d+), i32 (\d+), i32 (\d+), i32 (\d+), i32 (\d+), i32 (\d+), i32 (\d+), i32 (\d+), i32 (\d+)\]', args, re.M | re.I)
                args = [int(matchObj.group(x+1)) for x in range(10)]
            local_print_items[line_num]['args_type'] = args
    else:
        pattern = re.compile(
            r'typeof_stru_member(\d+) = internal global (.+), align 4')   #
        result = pattern.findall(context)
        if result:
            for (line_num, args) in result:
                if ('[10 x i32] zeroinitializer' == args):
                    args = [0 for x in range(10)]
                else:
                    matchObj = re.match(
                        r'<[^>]+> <{ (.+) zeroinitializer }>', args, re.M | re.I)
                    pattern = re.compile(
                        r'i32 (\d+)')   #
                    result = pattern.findall(matchObj.group(1))
                    args = [0 for x in range(10)]
                    for i in range(0, len(result)):
                        args[i] = result[i]
                    for j in range(i+1, 10):
                        args[j] = '0'

                local_print_items[line_num]['args_type'] = args

    # print(local_print_items)
    for (line_num, item) in local_print_items.items():
        addr = item['addr']
        print_items[addr] = {'line': line_num,
                             'str': item['str'], 'args': item['args'], 'args_t': item['args_type'], 'file': file_path}
    return


def tryLock(f):
    try:
        fcntl.flock(f, fcntl.LOCK_EX | fcntl.LOCK_NB)
        return True
    except Exception as e:
        return False


def tryUnLock(f):
    try:
        fcntl.flock(f, fcntl.LOCK_UN)
        return True
    except Exception as e:
        return False

# Make the records of the files using FastLog in this project.
# @srcFile: The full path of the c file
# @includes: The include path strings


def fastlog_make_record(srcFile: str, projPath: str, includes: str):
    relaPath = os.path.relpath(srcFile, projPath)

    # get all '*.c' files use fastlog module
    appear_cnt = first_preprocess(srcFile, projPath, includes)
    if appear_cnt:
        # count: Times 'fastlog' called
        # addr_start: The start addr alloc for tag
        # addr_len: The addrs alloc for tag
        # re_alloc: If this file addrs need to realloc
        # new_file: If this file is new add
        recordItem = {'file': relaPath, 'abs_path': srcFile,
                      'count': appear_cnt, 'addr_start': 0, 'addr_len': 0, 're_alloc': False, 'new_file': True}
    else:
        return

    fastlogRecFile = os.path.join(projPath, 'fastlog_out', 'fastlog.json')
    mkdirs(os.path.dirname(fastlogRecFile))
    recordFile = open(fastlogRecFile, mode='a+')

    while tryLock(recordFile) != True:
        time.sleep(0.001)

    recordItems = {}
    context = recordFile.read()
    if context:
        recordItems = json.loads(context)
    recordItemHash = hashlib.md5(
        (srcFile).encode()).hexdigest()
    recordItems[recordItemHash] = recordItem
    recordJson = json.dumps(recordItems)
    # print(recordJson)
    recordFile.write(recordJson)
    tryUnLock(recordFile)
    recordFile.close()


def read_record(projPath: str, fileName: str):
    recordItems = {}
    fastlogRecFile = os.path.join(
        projPath, 'fastlog_out', fileName)
    if os.path.isfile(fastlogRecFile):
        recordFile = open(fastlogRecFile, mode='r')
        context = recordFile.read()
        recordFile.close()
        recordItems = json.loads(context)
    return recordItems


# @srcFile: The full path of the c file
# @includes: The include path strings
def fastlog(srcFile: str, projPath: str, includes: str):
    recordItems = {}
    recordItemsOld = {}

    relaPath = os.path.relpath(srcFile, projPath)

    recordItemsOld = read_record(projPath, 'fastlog.old.json')
    recordItems = read_record(projPath, 'fastlog.json')
    if not recordItems:
        return False

    modeAddrSize = malloc_addr(recordItemsOld, recordItems)
    configHeaderDir = os.path.join(
        projPath, 'inc', os.path.basename(projPath))
    mkdirs(configHeaderDir)
    configHeaderPath = os.path.join(
        configHeaderDir, 'fastlog_config.h')
    configHeader = open(configHeaderPath, mode='w')
    header = '''
#ifndef __{0}_H__
#define __{0}_H__

#define FASTLOG_SIZE_{0} {1}

#endif
'''.format(os.path.basename(projPath).upper(), modeAddrSize)
    configHeader.write(header)

    fastlog_lines_file = os.path.join(
        projPath, 'fastlog_out', "fastlog_lines.json")
    fastlog_lines_f = open(fastlog_lines_file, mode='w')
    print_items = {}

    for recordItem in recordItems.values():
        srcFile = recordItem['abs_path']
        # print(file)
        cppdefines = ' -D '+'CONFIG_ARM '
        cppdefines += " -D FASTLOG_FILE_ADDR=" + \
            str(recordItem['addr_start']) + \
            " -D USE_FASTLOG= -D PYTHON_SCOPE_PRE=static"
        out_file_p = second_preprocess(
            srcFile, projPath, includes, macro_def=cppdefines)
        get_fastlog_call(srcFile, out_file_p, print_items)
    print_json = json.dumps(print_items)
    fastlog_lines_f.write(print_json)

    return recordItems


def fastlog_clean(projPath: str):
    fastlogRecFile = os.path.join(projPath, 'fastlog_out', 'fastlog.json')
    if os.path.isfile(fastlogRecFile):
        os.remove(fastlogRecFile)

    fastlogOldRecFile = os.path.join(
        projPath, 'fastlog_out', 'fastlog.old.json')
    if os.path.isfile(fastlogOldRecFile):
        os.remove(fastlogOldRecFile)


def fastlog_init(projPath: str):
    fastlogRecFile = os.path.join(projPath, 'fastlog_out', 'fastlog.json')
    fastlogOldRecFile = os.path.join(
        projPath, 'fastlog_out', 'fastlog.old.json')

    if os.path.isfile(fastlogOldRecFile):
        os.remove(fastlogOldRecFile)

    if os.path.isfile(fastlogRecFile):
        os.rename(fastlogRecFile, fastlogOldRecFile)


if __name__ == '__main__':  # noqa
    import argparse

    parser = argparse.ArgumentParser(
        description='fastlog')

    parser.add_argument(
        '-PROJECT',
        type=str,
        help='project path')

    parser.add_argument(
        '-NAME',
        type=str,
        nargs='?',
        help='project name, default: %(default)s',
        default='main')

    parser.add_argument(
        '-FILE',
        type=str,
        nargs='?',
        help='full path of source file',
        default=None)

    parser.add_argument(
        '-INCLUDE_PATHS',
        type=str,
        nargs='?',
        help='include paths, like "-IFastLog/inc"',
        default=None)

    parser.add_argument(
        '-STAGE',
        choices=['init', 'clean', 'record', 'final'],
        type=str,
        nargs='?',
        help='stage, default: %(default)s',
        default='init')

    args = parser.parse_args()
    match args.STAGE:
        case 'init':
            fastlog_init(args.PROJECT)
        case 'clean':
            print("sdddddddddddddd")
            fastlog_clean(args.PROJECT)
        case 'record':
            fastlog_make_record(args.FILE, args.PROJECT, args.INCLUDE_PATHS)
        case 'final':
            fastlog(args.FILE, args.PROJECT, args.INCLUDE_PATHS)
