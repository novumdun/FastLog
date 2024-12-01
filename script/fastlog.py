import hashlib
import json
import shutil
import platform
import subprocess
import re
import os

# if files use 'fastlog' module
def is_fastlog_files(file_name):
    matchObj = re.match(r'(.+).c$', file_name, re.M | re.I)
    if matchObj:
        file = open(file_name, mode='r', encoding='UTF-8', errors='ignore')
        context = file.read()
        file.close()

        pattern = re.compile(r'STR_BUF_WRITE_STRU')   #
        result = pattern.findall(context)
        return len(result)
    return 0


def mkdir(path):
    if True != os.path.exists(path):
        os.makedirs(path)  # makedirs


def file_preprocess(file, inc_paths, out_path, macro_def=''):
    inc_path = ''
    for i_path in inc_paths:
        inc_path += ' -I '+i_path
    macro_defs = macro_def

    (relative_dir, file_name) = os.path.split(file)
    out_file_dir = os.path.join(out_path, 'build/myout', relative_dir)
    mkdir(out_file_dir)
    out_file = os.path.join(out_file_dir, file_name+'.i')

    cmd_str = 'clang -E '+file + ' ' + \
        inc_path+macro_defs+' > '+out_file

    # print(cmd_str)
    ret = subprocess.check_output(cmd_str, shell=True)
    sys = platform.system()
    if sys == "Windows":
        # print(ret.decode('gbk'))  #
        pass
    else:
        # print(ret)
        pass
    return out_file


def file_compile_asm(file, inc_paths, out_path, CC, CFLAGS):
    inc_path = ''
    for i_path in inc_paths:
        inc_path += ' -I '+i_path

    macro_defs = " -D PYTHON_SATRT= -D PYTHON_END= -D PYTHON_STRU_START= -D PYTHON_STRU_END= -D PYTHON_GET=" + \
        " -D FILE_ADDR="+str(0)

    (relative_dir, file_name) = os.path.split(file)
    out_file_dir = os.path.join(out_path, 'build/myout', relative_dir)
    mkdir(out_file_dir)
    out_file = os.path.join(out_file_dir, file_name+'.s')
    if True == os.path.isfile(out_file):
        os.remove(out_file)

    cmd_str = CC+' -S '+CFLAGS+file + inc_path + macro_defs
    # print(cmd_str)
    ret = subprocess.check_output(cmd_str, shell=True)

    shutil.move(file_name+'.s', out_file)

    sys = platform.system()
    if sys == "Windows":
        # print(ret.decode('gbk'))  #
        pass
    else:
        # print(ret)
        pass


def get_count_lvl(count):
    lvl = [0x40, 0x80, 0x100]
    for i in lvl:
        if count < i:
            return i
    return (count/0x100)*0x100+0x100


def need_malloc_addr(count_old, count):
    lvl = get_count_lvl(count)
    lvl_old = get_count_lvl(count_old)
    lvl_chg = lvl-lvl_old
    if (0 < lvl_chg) or (-2 >= lvl_chg):
        return True

    return False


def malloc_addr(record_items_old, record_items):
    addrs_free = []
    for record_item_hash, record_item in record_items.items():
        flag = False
        for record_item_hash_old, record_item_old in record_items_old.items():
            if (record_item_hash_old == record_item_hash) and (record_item_old['file'] == record_item['file']):
                record_items[record_item_hash]['new_file'] = False
                if need_malloc_addr(record_item_old['count'], record_item['count']):
                    record_items[record_item_hash]['re_alloc'] = True
                flag = True
                break
        if False == flag:
            record_items[record_item_hash]['re_alloc'] = False

    [addr, len] = [0, 0]
    for record_item_hash, record_item in record_items.items():
        if (False == record_item['new_file']) and (False == record_items[record_item_hash]['re_alloc']):
            record_items[record_item_hash]['addr_start'] = record_items_old[record_item_hash]['addr_start']
            record_items[record_item_hash]['addr_len'] = record_items_old[record_item_hash]['addr_len']
            if (addr + len) < record_items[record_item_hash]['addr_start']:
                addrs_free.append(
                    [addr, record_items[record_item_hash]['addr_start']-addr-len])
            addr = record_items[record_item_hash]['addr_start']
            len = record_items[record_item_hash]['addr_len']
    addrs_free.append([addr+len, 0x10000-(addr + len)])
    # print(addrs_free)

    for record_item_hash, record_item in record_items.items():
        if (True == record_item['new_file']) or (True == record_item['re_alloc']):
            for (i, (addr, len)) in enumerate(addrs_free):
                lvl = get_count_lvl(record_item['count'])
                if len >= lvl:
                    record_items[record_item_hash]['addr_start'] = addr
                    record_items[record_item_hash]['addr_len'] = get_count_lvl(
                        record_item['count'])
                    if lvl == len:
                        del addrs_free[i]
                    addrs_free[i][0] = addr+lvl
                    addrs_free[i][1] = len-lvl
                    break
    # print(addrs_free)


def get_fastlog_call(file_path, out_file_path, print_items):
    # print(out_file_path)
    cmd_str = "clang --target=arm-none-eabi -S -O0 -emit-llvm " + \
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
    pattern = re.compile(r'gen_frame(\d+)\.global_cnt = (\d+) \+ (\d+)')
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
        r'sizeof_stru_member(\d+) = internal global \[10 x i32\] (.+), align 4')   #
    result = pattern.findall(context)
    if result:
        for (line_num, args) in result:
            if('zeroinitializer' == args):
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
                if('[10 x i32] zeroinitializer' == args):
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
        r'typeof_stru_member(\d+) = internal global \[10 x i32\] (.+), align 4')   #
    result = pattern.findall(context)
    if result:
        for (line_num, args) in result:
            if('zeroinitializer' == args):
                args = [0 for x in range(10)]
            else:
                matchObj = re.match(
                    r'\[i32 (\d), i32 (\d), i32 (\d), i32 (\d), i32 (\d), i32 (\d), i32 (\d), i32 (\d), i32 (\d), i32 (\d)\]', args, re.M | re.I)
                args = [int(matchObj.group(x+1)) for x in range(10)]
            local_print_items[line_num]['args_type'] = args
    else:
        pattern = re.compile(
            r'typeof_stru_member(\d+) = internal global (.+), align 4')   #
        result = pattern.findall(context)
        if result:
            for (line_num, args) in result:
                if('[10 x i32] zeroinitializer' == args):
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


def fastlog(srcs_stru, includes, out_path):
    record_items = {}
    record_items_old = {}

    # get all '*.c' files use fastlog module
    for c_src in srcs_stru:
        appear_cnt = is_fastlog_files(c_src)
        if appear_cnt:
            # count: Times 'fastlog' called
            # addr_start: The start addr alloc for tag
            # addr_len: The addrs alloc for tag
            # re_alloc: If this file addrs need to realloc
            # new_file: If this file is new add
            record_item = {'file': srcs_stru[c_src]['file'], 'abs_path': c_src,
                           'count': appear_cnt, 'addr_start': 0, 'addr_len': 0, 're_alloc': False, 'new_file': True}

            record_item_hash = hashlib.md5(
                (c_src).encode()).hexdigest()
            record_items[record_item_hash] = record_item

    fastlog_file = os.path.join(out_path + "fastlog.json")
    if os.path.isfile(fastlog_file):
        record_json_f = open(fastlog_file, mode='r')
        context = record_json_f.read()
        record_json_f.close()
        record_items_old = json.loads(context)

    if 0 == len(record_items):
        record_json = json.dumps(record_items)
        # print(record_json)
        record_json_f = open(fastlog_file, mode='w')
        record_json_f.write(record_json)
        record_json_f.close()
        return

    malloc_addr(record_items_old, record_items)

    record_json = json.dumps(record_items)
    # print(record_json)
    record_json_f = open(fastlog_file, mode='w')
    record_json_f.write(record_json)
    record_json_f.close()

    # get
    fastlog_lines_file = os.path.join(out_path + "fastlog_lines.json")
    fastlog_lines_f = open(fastlog_lines_file, mode='w')
    print_items = {}

    for record_item in record_items.values():
        file = record_item['abs_path']
        # print(file)
        cppdefines = ''
        for define in srcs_stru[file]['defs']:
            cppdefines += ' -D '+define + ' '
        cppdefines += includes
        cppdefines += ' -D '+'CONFIG_ARM '
        cppdefines += " -D FILE_ADDR=" + str(record_item['addr_start']) + \
            " -D PYTHON_SATRT= -D PYTHON_END= -D PYTHON_STRU_START= -D PYTHON_STRU_END= -D PYTHON_GET= -D PYTHON_SCOPE_PRE=static"
        out_file_p = file_preprocess(
            file, srcs_stru[file]['incs'], out_path, macro_def=cppdefines)
        get_fastlog_call(file, out_file_p, print_items)
    print_json = json.dumps(print_items)
    fastlog_lines_f.write(print_json)

    return record_items
