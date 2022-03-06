project('com.github.jeysonflores.vault', ['cpp', 'c'], 
          version: '0.1.0',
    meson_version: '>= 0.50.0',
  default_options: [ 'warning_level=2',
                     'cpp_std=gnu++17',
                   ],
)

gnome = import('gnome')

asresources = gnome.compile_resources (
    'as-resources', 'data/' + meson.project_name() + '.gresource.xml',
    source_dir: 'data',
    c_name: 'as'
)

subdir('data')

executable(
	meson.project_name(),
	asresources,
	['src/Vault.hpp'],
	['src/Application.hpp', 'src/Application.cpp'], 
	['src/MainWindow.hpp', 'src/MainWindow.cpp'],
	['src/Style.hpp'],
	['src/Views/MainView.hpp', 'src/Views/MainView.cpp'],
	dependencies: [
		dependency('gtkmm-3.0'),
		dependency('granite'),
		dependency('fmt'),
	],
	install: true,
)

meson.add_install_script('build-aux/post_install.py')