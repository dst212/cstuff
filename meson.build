# Meson build file for cstuff libraries

project('cstuff', 'c', version: '1.0', license: 'lgplv3', default_options: 'c_std=c11')

inc = include_directories('cstuff')
cc = meson.get_compiler('c')

# miscstuff library
miscstuff_inc = include_directories('miscstuff')
miscstuff = shared_library(
	'miscstuff',
	'miscstuff/miscstuff.h',
	include_directories: miscstuff_inc,
	dependencies: cc.find_library('m'),
	install: true
)
miscstuff_dep = declare_dependency(include_directories: miscstuff_inc, link_with: miscstuff)

# strstuff library
strstuff_inc = include_directories('strstuff')
strstuff = shared_library(
	'strstuff',
	'cstuff/strstuff.h',
	include_directories: strstuff_inc,
	install: true
)
strstuff_dep = declare_dependency(include_directories: strstuff_inc, link_with: strstuff)

# chstuff library
chstuff_inc = include_directories('chstuff')
chstuff = shared_library(
	'chstuff',
	'cstuff/chstuff.h',
	include_directories: chstuff_inc,
	install: true
)
chstuff_dep = declare_dependency(include_directories: chstuff_inc, link_with: chstuff)

# ncstuff library
ncstuff_inc = include_directories('ncstuff')
ncstuff = shared_library(
	'ncstuff',
	'cstuff/ncstuff.h',
	include_directories: ncstuff_inc,
	dependencies: cc.find_library('ncurses'),
	install: true
)
ncstuff_dep = declare_dependency(include_directories: ncstuff_inc, link_with: ncstuff)

# All the libraries in one dependency
cstuff = [
	miscstuff,
	strstuff,
	chstuff,
	ncstuff
]
inc = [
	miscstuff_inc,
	strstuff_inc,
	chstuff_inc,
	ncstuff_inc
]
cstuff_dep = declare_dependency(include_directories: inc, link_with: cstuff)
