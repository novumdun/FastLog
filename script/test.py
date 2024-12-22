from fastlog import fastlog_init, fastlog_clean, fastlog_make_record, fastlog, file_compile
from fastlog_display import display_flog
import subprocess
import os
import time

def shell_cmd(cmd: str):
    print(cmd)
    ret = subprocess.check_output(cmd, shell=True)
    print(ret.decode("utf-8"))

dir = os.path.dirname(__file__)
projPath = os.path.join(dir, '..')
includes = f'-I{projPath}/inc -I{projPath}/fastlog_out/inc'
fastlog_clean(projPath)
fastlog_init(projPath)

srcFile = os.path.join(projPath, 'src/fastlog.c')
cmd = 'gcc ' + ' -c -g ' + srcFile + ' ' + includes + \
    ' -D FASTLOG_STAGE=FASTLOG_STAGE_COMP'
shell_cmd(cmd)

srcFile = os.path.join(projPath, 'test/fastlog_test.c')
cmd = 'gcc ' + ' -c -g ' + srcFile + ' ' + includes + \
    ' -D FASTLOG_STAGE=FASTLOG_STAGE_COMP'
print(cmd)
ret = subprocess.check_output(cmd, shell=True)
print(ret.decode("utf-8"))

srcFile = os.path.join(projPath, 'test/test.c')
fastlog_make_record(srcFile, projPath, includes)
fastlog(srcFile, projPath, 'test', includes)
cmd = file_compile(srcFile, projPath, 'gcc ' +
                   ' -c -g ' + srcFile + ' ' + includes)
shell_cmd(cmd)

cmd = 'gcc ' + ' -o Test ' + ' test.o fastlog_test.o fastlog.o'
shell_cmd(cmd)

cmd = './Test'
shell_cmd(cmd)

time.sleep(1)
display_flog()
