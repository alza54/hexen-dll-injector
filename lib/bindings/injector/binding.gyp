{
  'targets': [
    {
      'target_name': 'injector',
      'sources': [
        "init.cc",
        "src/Injector.cc",
      ],
      'include_dirs': [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
