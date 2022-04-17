project('com.github.jeysonflores.vault', ['vala', 'c'], 
          version: '0.0.0',
    meson_version: '>= 0.50.0',
)

i18n = import('i18n')
gnome = import('gnome')

add_project_arguments(
    '-DGETTEXT_PACKAGE="@0@"'.format(meson.project_name()),
    language: 'c'
)

conf = configuration_data()
conf.set_quoted('GETTEXT_PACKAGE', meson.project_name())
configure_file(output: 'config.h', configuration: conf)
config_h_dir = include_directories('.')

c_args = [
  '-include', 'config.h'
]


subdir('data')
subdir('po')


executable(
  meson.project_name(),
  ['src/Vault.vala'],
  ['src/MainWindow.vala'],
  ['src/Views/MainView.vala'],
  ['src/Views/WelcomeView.vala'],
  ['src/Models/Note.vala'],
  ['src/Proxies/Note.vala'],
  c_args: c_args,
  dependencies: [
    dependency('glib-2.0'),
    dependency('gobject-2.0'),
    dependency('granite'),
    dependency('gtk+-3.0'),
    dependency('gdk-pixbuf-2.0'),
    dependency('libhandy-1', version: '>= 0.90.0'),
  ],
  install: true
)

meson.add_install_script('build-aux/post_install.py')