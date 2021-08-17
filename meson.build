# Copyright 2021 thatlittlegit
# SPDX-License-Identifier: LGPL-3.0-or-later
project('janitor', 'c',
  version: '0.1.0',
  license: 'LGPL-3.0-or-later',
  default_options: ['c_std=c99', 'warning_level=3'],
)

subdir('src')
subdir('include')

executable('testexe', 'test.c',
  dependencies: janitor_dep,
  install: false,
)
