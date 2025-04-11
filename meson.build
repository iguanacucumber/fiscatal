project(
	'fiscatal',
	'c',
	version: '0.1',
	default_options: [
		'warning_level=3',
		'c_args=-flto -O2 -march=native -mtune=native -ftree-vectorize -fomit-frame-pointer',
	],
)

# Check for the fast Mold linker
mold_check = run_command('which', 'mold', check: false)
if mold_check.returncode() == 0
	add_project_arguments('-fuse-ld=mold', language: 'c')
endif

raylib = dependency('raylib', required: true)
dependencies = [raylib]

# RayGUI is a header-only library, so we'll handle it differently
raygui_inc = include_directories('submodules/raygui/src')
add_project_arguments('-DRAYGUI_IMPLEMENTATION', language: 'c')

# Source files
src_files = [
	'src/main.c',
]

binary = executable(
	'fiscatal',
	src_files,
	install: true,
	dependencies: dependencies,
	include_directories: raygui_inc,
)

run_command('strip', binary.full_path(), check: false)
