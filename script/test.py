from fastlog import fastlog_init, fastlog_clean, fastlog_make_record, fastlog, file_compile
import subprocess

projPath = '/home/dengbo/workspace/cabin/FastLog'
includes = '-I/home/dengbo/workspace/cabin/FastLog/inc -I/home/dengbo/workspace/cabin/FastLog/fastlog_out/inc'
fastlog_clean(projPath)
fastlog_init(projPath)

srcFile = '/home/dengbo/workspace/cabin/FastLog/src/fastlog.c'
cmd = 'gcc ' + ' -c -g ' + srcFile + ' ' + includes + \
    ' -D FASTLOG_STAGE=FASTLOG_STAGE_COMP'
print(cmd)
ret = subprocess.check_output(cmd, shell=True)
print(ret.decode("utf-8"))

srcFile = '/home/dengbo/workspace/cabin/FastLog/test/fastlog_test.c'
cmd = 'gcc ' + ' -c -g ' + srcFile + ' ' + includes + \
    ' -D FASTLOG_STAGE=FASTLOG_STAGE_COMP'
print(cmd)
ret = subprocess.check_output(cmd, shell=True)
print(ret.decode("utf-8"))

srcFile = '/home/dengbo/workspace/cabin/FastLog/test/test.c'
fastlog_make_record(srcFile, projPath, includes)
fastlog(srcFile, projPath, 'test', includes)
cmd = file_compile(srcFile, projPath, 'gcc ' +
                   ' -c -g ' + srcFile + ' ' + includes)
print(cmd)
ret = subprocess.check_output(cmd, shell=True)
print(ret.decode("utf-8"))

cmd = 'gcc ' + ' -o Test ' + ' test.o fastlog_test.o fastlog.o'
print(cmd)
ret = subprocess.check_output(cmd, shell=True)
print(ret.decode("utf-8"))
