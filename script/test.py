from fastlog import fastlog_init, fastlog_clean, fastlog_make_record, fastlog

srcFile = '/home/dengbo/workspace/cabin/FastLog/test/test.c'
projPath = '/home/dengbo/workspace/cabin/FastLog'
includes = '-I/home/dengbo/workspace/cabin/FastLog/inc -I/home/dengbo/workspace/cabin/FastLog/src -I/home/dengbo/workspace/cabin/FastLog/fastlog_out/inc'
fastlog_clean(projPath)
fastlog_init(projPath)

fastlog_make_record(srcFile, projPath, includes)
fastlog(srcFile, projPath, 'test', includes)
