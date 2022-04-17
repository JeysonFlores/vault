project('com.github.jeysonflores.vault.Daemon', ['cpp', 'c'], 
          version: '0.1.0',
    meson_version: '>= 0.50.0',
  default_options: [ 'warning_level=2',
                     'cpp_std=gnu++17',
                   ],
)

install_data(
    'data/' + meson.project_name() + '.service',
    install_dir: join_paths(get_option('datadir'), 'dbus-1/services')
)

executable(
      meson.project_name(),
      ['src/VaultDaemon.cpp'],
      ['src/Adaptors/Note.hpp'],
      ['src/Interfaces/Note.hpp', 'src/Interfaces/Note.cpp'],
      ['src/Services/DataManager.hpp', 'src/Services/DataManager.cpp'],
      ['src/Utils/Logger.hpp', 'src/Utils/Logger.cpp'], 
      dependencies: [
        dependency('sdbus-c++'),
        dependency('sqlite_modern_cpp'),
      ],
      install: true
)