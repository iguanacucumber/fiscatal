project(
  'fiscatal',
  'c',
  version: '0.1',
  default_options: [
    'warning_level=3',
    'c_args=-flto -O3 -ffast-math -march=native -mtune=native -fomit-frame-pointer',
  ],
)

# Check for the fast Mold linker
mold_check = run_command('sh', '-c', 'ld --version | grep mold', check: false)
if mold_check.returncode() == 0
  add_project_arguments('-fuse-ld=mold', language: 'c')
endif

sdl3_dep = dependency('sdl3', required : true)

binary = executable('fiscatal', 'src/main.c', install: true, dependencies: sdl3_dep)
run_command('strip', binary.full_path(), check: false)
