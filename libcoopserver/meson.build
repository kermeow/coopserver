project('coopserver', 'c')
src = [
	'src/main.c', 'src/libdetour.c', 'src/crash_handler.c',
	'src/hooks/pc_main.c', 'src/hooks/configfile.c']
inc = include_directories('include')
shared_library('coopserver', src, include_directories: inc)