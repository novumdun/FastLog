import hashlib
import json
import shutil
import platform
import subprocess
import re
import copy


def get_project_src(project):
    libs_stru = {}
    source_stru = {}
    for group in project:
        # print(group)

        lib_name = group['name']
        lib_source_dir = group['path']

        libs_stru[lib_name] = {'lib_source_dir': lib_source_dir}

        libs_stru[lib_name]['lib_sources'] = []
        for c_src_obj in group['src']:
            source = os.path.abspath(str(c_src_obj))
            libs_stru[lib_name]['lib_sources'].append(source)

        libs_stru[lib_name]['lib_include_dirs'] = []
        for i_path_obj in group['CPPPATH']:
            libs_stru[lib_name]['lib_include_dirs'].append(str(i_path_obj))

        libs_stru[lib_name]['lib_compile_defs'] = []
        if 'CPPDEFINES' in group:
            for cppdef_src_obj in group['CPPDEFINES']:
                libs_stru[lib_name]['lib_compile_defs'].append(
                    str(cppdef_src_obj))

    # print(libs_stru)

    source_stru = {}
    for key, item in libs_stru.items():
        lib_source_dir = item['lib_source_dir']
        lib_compile_defs = item['lib_compile_defs']
        lib_sources = item['lib_sources']
        lib_include_dirs = item['lib_include_dirs']

        # print('lib')
        # print(key)
        # print('lib_source_dir')
        # print(lib_source_dir)
        # print('lib_compile_defs')
        # print(lib_compile_defs)
        # print('lib_sources\t')
        # print(lib_sources)
        # print('lib_include_dirs')
        # print(lib_include_dirs)

        for source in lib_sources:
            origin_source = source

            source_stru[str(source)] = {}
            source_stru[str(source)]['file'] = origin_source
            source_stru[str(source)]['lib'] = key
            source_stru[str(source)]['incs'] = copy.deepcopy(lib_include_dirs)
            source_stru[source]['defs'] = copy.deepcopy(lib_compile_defs)
            # print("source_stru[source]['defs']")
            # print(source_stru[source]['defs'])

    return (source_stru)


def get_oneos_root_path():
    cwd = os.getcwd()
    print(cwd)
    print(os.path.abspath(cwd))
    matchObj = re.match(r'(.+)/([^/]+)/([^/]+)$', cwd, re.M | re.I)
    if matchObj:
        oneos_path = str(matchObj.group(1))
    else:
        matchObj = re.match(r'(.+)\\([^\\]+)\\([^\\]+)$', cwd, re.M | re.I)
        oneos_path = str(matchObj.group(1))
    return oneos_path


def MyStartCompile(target, objects, record_items):
    if None == record_items:
        return

    from build_tools import Env

    # merge all objects into one list
    def one_list(l):
        lst = []
        for item in l:
            if type(item) == type([]):
                lst += one_list(item)
            else:
                lst.append(item)
        return lst

    # handle local group
    def local_group(group, objects, record_items):
        if 'LOCAL_CCFLAGS' in group or 'LOCAL_CPPPATH' in group or 'LOCAL_CPPDEFINES' in group or 'LOCAL_ASFLAGS' in group:
            CCFLAGS = Env.get('CCFLAGS', '') + group.get('LOCAL_CCFLAGS', '')
            CPPPATH = Env.get('CPPPATH', ['']) + \
                group.get('LOCAL_CPPPATH', [''])
            CPPDEFINES = Env.get(
                'CPPDEFINES', ['']) + group.get('LOCAL_CPPDEFINES', [''])
            ASFLAGS = Env.get('ASFLAGS', '') + group.get('LOCAL_ASFLAGS', '')

            for source in group['src']:
                objects.append(Env.Object(source, CCFLAGS=CCFLAGS, ASFLAGS=ASFLAGS,
                                          CPPPATH=CPPPATH, CPPDEFINES=CPPDEFINES))

            return True

        for source in group['src']:
            for obj in objects:
                # print(type(obj))
                if "<class 'SCons.Node.FS.File'>" == str(type(obj)):
                    if source.abspath == obj.abspath:
                        for hash, record_item in record_items.items():
                            origin_p = (os.path.abspath(
                                str(obj.path_elements[-1])))
                            if origin_p == record_item['abs_path']:
                                print(record_item['abs_path'])
                                objects.remove(obj)
                                CCFLAGS = Env.get('CCFLAGS', '')
                                CPPPATH = Env.get('CPPPATH', [''])
                                CPPDEFINES = Env.get('CPPDEFINES', [''])
                                ASFLAGS = Env.get('ASFLAGS', '')
                                macro_defs = " -D '__PYTHON_SCOPE_PRE=' -D FILE_ADDR=" + \
                                    str(record_item['addr_start'])
                                CCFLAGS += macro_defs
                                print('CCFLAGS ' + CCFLAGS)
                                objects.append(Env.Object(source, CCFLAGS=CCFLAGS, ASFLAGS=ASFLAGS,
                                                          CPPPATH=CPPPATH, CPPDEFINES=CPPDEFINES))

        return False

    objects = one_list(objects)

    program = None
    lib_name = None
    '''
    # check whether special buildlib option
    lib_name = GetOption('buildlib')
    '''
    if lib_name:
        objects = []  # remove all of objects
        # build library with special component
        for Group in Projects:
            if Group['name'] == lib_name:
                lib_name = GroupLibName(Group['name'], Env)
                if not local_group(Group, objects, record_items):
                    objects = Env.Object(Group['src'])

                program = Env.Library(lib_name, objects)

                # add library copy action
                Env.BuildLib(lib_name, program)

                break
    else:
        # remove source files with local flags setting
        for group in Projects:
            if 'LOCAL_CCFLAGS' in group or 'LOCAL_CPPPATH' in group or 'LOCAL_CPPDEFINES' in group:
                for source in group['src']:
                    for obj in objects:
                        if source.abspath == obj.abspath or (len(obj.sources) > 0 and source.abspath == obj.sources[0].abspath):
                            objects.remove(obj)

        # re-add the source files to the objects
        for group in Projects:
            local_group(group, objects, record_items)

        no_exec = GetOption('no_exec')
        #print("no_exec:%d"% no_exec)
        # if no_exec != 1 :
        # Env.Install(out_dir,)
        program = Env.Program(target, objects)
        '''
        for obj in objects:
            if hasattr(obj, 'abspath') and len(obj.abspath) > 0 :
                print(obj.abspath)
            elif hasattr(obj, 'sources') and len(obj.sources) > 0 and  hasattr(obj.sources, 'abspath') and len(obj.sources[0].abspath) > 0 :
                print(obj.sources[0].abspath)
        '''

    EndBuilding(target, program)


def scons_asm():
    (c_srcs, i_paths) = get_project_src(Projects)
    file = r"D:\Workspace\OneOS\oneos-2.0\projects\stm32l475-atk-pandora\application\easy_print\easy_print_ext.c"
    path = os.path.abspath(file)
    cppdefines = ''
    for define in env['CPPDEFINES']:
        cppdefine = define[0]
        cppdefines += ' -D '+cppdefine+'= '
    cppdefines += " -D PYTHON_SATRT= -D PYTHON_END= -D PYTHON_STRU_START= -D PYTHON_STRU_END="

    CFLAGS = ''
    matchObj = re.match(r'(.+) (-O[^ ]+) (.+)', osconfig.CFLAGS, re.M | re.I)
    if matchObj:
        CFLAGS = ' '+matchObj.group(2)+' '
        print(CFLAGS)
    CFLAGS += osconfig.DEVICE
    file_compile_asm(path, inc_paths, proj_path, out_path, osconfig.CC, CFLAGS)
