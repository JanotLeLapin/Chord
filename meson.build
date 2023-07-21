project('chord', 'c')

include = include_directories('include')

deps = [
  dependency('notcurses-core'),
  dependency('libcurl'),
  dependency('jansson')
]

executable('chord',
  'src/main.c',
  'src/api/user.c',
  'src/structures/user.c',
  'src/ui/util.c', 'src/ui/userlist.c', 'src/ui/messages.c', 'src/ui/profile.c',
  dependencies: deps,
  include_directories: include)
