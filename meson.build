project('ecoint', 'c',
  license: 'LGPL-2.1-only',
  meson_version: '>=1.1.0')

cc = meson.get_compiler('c')
libm = cc.find_library('m', required: false)
inc = include_directories('.')

library_type = get_option('library_type')

if library_type == 'static'
  static_library('ecoint', 'ecoint.c',
    include_directories: inc,
    dependencies: libm)

  static_library('ecoint_freestanding', 'ecoint_freestanding.c',
    include_directories: inc,
    c_args: ['-ffreestanding'])

elif library_type == 'dynamic'
  shared_library('ecoint', 'ecoint.c',
    include_directories: inc,
    dependencies: libm)

  shared_library('ecoint_freestanding', 'ecoint_freestanding.c',
    include_directories: inc,
    c_args: ['-ffreestanding'])

else # 'all'
  both_libraries('ecoint', 'ecoint.c',
    include_directories: inc,
    dependencies: libm)

  both_libraries('ecoint_freestanding', 'ecoint_freestanding.c',
    include_directories: inc,
    c_args: ['-ffreestanding'])
endif
