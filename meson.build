project('exp-socket', 'c',
        meson_version : '>=0.50.0',
        version : '1.0.0',
        license : 'MIT',
        default_options : ['warning_level=3', 'c_std=c11'])

# TCP
######################################################
tcp_server_src = []
tcp_client_src = []
subdir('tcp/server-src')
subdir('tcp/client-src')

executable('tcp-server', tcp_server_src)
executable('tcp-client', tcp_client_src)
######################################################

# UDP
######################################################
udp_server_src = []
udp_client_src = []
subdir('udp/server-src')
subdir('udp/client-src')

executable('udp-server', udp_server_src)
executable('udp-client', udp_client_src)
######################################################
