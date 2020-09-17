# Meson build file for cstuff libraries

project('cstuff', 'c', version: '1.0', license: 'lgplv3', default_options: 'c_std=c11')

inc = include_directories('cstuff')
cc = meson.get_compiler('c')

# miscstuff library
miscstuff = shared_library(
	'miscstuff',
	'cstuff/miscstuff.h',
	include_directories: inc,
	dependencies: cc.find_library('m'),
	install: true
)
miscstuff_dep = declare_dependency(include_directories: inc, link_with: miscstuff)

# strstuff library
strstuff = shared_library(
	'strstuff',
	'cstuff/strstuff.h',
	include_directories: inc,
	install: true
)
strstuff_dep = declare_dependency(include_directories: inc, link_with: strstuff)

# chstuff library
chstuff = shared_library(
	'chstuff',
	'cstuff/chstuff.h',
	include_directories: inc,
	install: true
)
chstuff_dep = declare_dependency(include_directories: inc, link_with: chstuff)

# ncstuff library
ncstuff = shared_library(
	'ncstuff',
	'cstuff/ncstuff.h',
	include_directories: inc,
	dependencies: cc.find_library('ncurses'),
	install: true
)
ncstuff_dep = declare_dependency(include_directories: inc, link_with: ncstuff)

# All the libraries in one dependency
cstuff = [
	miscstuff,
	strstuff,
	chstuff,
	ncstuff
]

cstuff_dep = declare_dependency(include_directories: inc, link_with: cstuff)
