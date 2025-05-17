project('coopserver', 'c')

main_src = [
	'src/main.c', 'src/libdetour.c', 'src/crash_handler.c',
	'src/server/server_main.c',
	'src/coop/pc/configfile.c'
]
hooks_src = ['src/hooks/pc_main.c', 'src/hooks/configfile.c']

src = [main_src, hooks_src]
inc = include_directories('include')

shared_library('coopserver', src, include_directories: inc)