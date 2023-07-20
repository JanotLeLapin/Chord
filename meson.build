project('chord', 'c')

include = include_directories('include')

deps = [
  dependency('notcurses-core'),
  dependency('libcurl'),
  dependency('json-c')
]

executable('chord',
  'src/main.c',
  'src/ui/util.c', 'src/ui/userlist.c', 'src/ui/messages.c',
  dependencies: deps,
  include_directories: include)
