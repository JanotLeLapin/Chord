project('chord', 'c')

include = include_directories('include')

deps = [
  dependency('notcurses-core'),
  dependency('libcurl'),
  dependency('jansson')
]

executable('chord',
  'src/main.c',
  'src/api/api.c', 'src/api/user.c', 'src/api/channel.c',
  'src/structures/user.c',
  'src/ui/util.c', 'src/ui/userlist.c', 'src/ui/input.c', 'src/ui/messages.c', 'src/ui/profile.c',
  dependencies: deps,
  include_directories: include)
