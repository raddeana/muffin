### deployable
- build -> temp -> opt -> prod
- configure
  - contents
  - dependencies
  - portals
  - build
  - opt
  - manifest

### deploy architecture
git hook -> release -> deploy -> call (build || opt)
  - materials -> opt -> publish
  - dependencies -> build -> opt -> publish -> portal -> restart
  - clients -> build -> opt -> publish -> portal -> restart
