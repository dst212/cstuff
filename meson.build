# Meson build file for cstuff libraries

project('cstuff', 'c', version: '1.0', license: 'lgplv3', default_options: 'c_std=c11')

inc = include_directories('cstuff')

libs = [
	shared_library(
		'mathstuff',
		'csutff/mathstuff.h',
		include_directories: inc,
		install: true
	),
	shared_library(
		'strstuff',
		'cstuff/strstuff.h',
		include_directories: inc,
		install: true
	),
	shared_library(
		'chstuff',
		'cstuff/chstuff.h',
		include_directories: inc,
		install: true
	),
	shared_library(
		'ncstuff',
		'cstuff/ncstuff.h',
		include_directories: inc,
		install: true
	)
]

libsimple_dep = declare_dependency(include_directories: inc, link_with: libs)
