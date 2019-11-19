{
  "targets": [
    {
      "target_name": "opendds",
      "sources": [ "src/node_opendds.cc" ],
      'include_dirs': [ '$(ACE_ROOT)', '$(TAO_ROOT)', '$(DDS_ROOT)' ],
      'conditions': [
        ['OS in "linux mac"', {
          'link_settings': {
            'libraries': [ '-lOpenDDS_Dcps', '-lTAO_PortableServer',
                           '-lTAO_AnyTypeCode', '-lTAO', '-lACE' ],
            'ldflags': [ '-L$(ACE_ROOT)/lib', '-L$(DDS_ROOT)/lib' ],
          },
        }],
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_RTTI': 'YES',
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'OTHER_LDFLAGS': ['-L$(ACE_ROOT)/lib', '-L$(DDS_ROOT)/lib',
                              '-rpath $(ACE_ROOT)/lib', '-rpath $(DDS_ROOT)/lib' ],
          }
        }],
        ['OS=="win"', {
          'msvs_settings' : {
            'VCLinkerTool': {
              'AdditionalLibraryDirectories': [ '$(ACE_ROOT)/lib',
                                                '$(DDS_ROOT)/lib' ],
            },
          },
          'link_settings': {
            'libraries': [ 'OpenDDS_Dcps<(lib_suffix)',
                           'TAO_PortableServer<(lib_suffix)',
                           'TAO_AnyTypeCode<(lib_suffix)',
                           'TAO<(lib_suffix)', 'ACE<(lib_suffix)' ],
          },
        }]
      ],
    }
  ]
}
