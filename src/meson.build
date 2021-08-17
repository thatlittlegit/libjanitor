# Copyright 2021 thatlittlegit
# SPDX-License-Identifier: LGPL-3.0-or-later
janitor_src = files(
  'cell.c',
  'cell.h',
  'cleanup.c',
  'context.c',
)

arch = host_machine.cpu_family()
os = host_machine.system()

janitor_arch = files('arch/@0@-@1@.S'.format(arch, os))

janitor_lib = library('janitor', [janitor_src, janitor_arch],
  install: true,
  gnu_symbol_visibility: 'hidden',
)

janitor_dep = declare_dependency(link_with: janitor_lib)
