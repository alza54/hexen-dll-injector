<template>
  <div @click="selectDLL" class="drop" :class="statusInformer">
    <div class="drop-text">{{ dropText }}</div>
  </div>
</template>

<script lang="ts">

  import EventBus from '../../bus';
  import { InjectionStatus } from '../../enums';

  const { remote } = require('electron');
  const { dialog } = remote;

  export default {
    name: 'drop-area',
    data () {
      return {
        dropText: 'Select or drop DLL file here',
        injectionStatus: InjectionStatus.NotInjected
      }
    },
    methods: {
      selectDLL () {
        dialog.showOpenDialog(remote.getCurrentWindow(), {
          title: 'Select DLL file',
          filters: [
            {
              name: '*.dll',
              extensions: [ 'dll' ]
            }
          ]
        }, path => {

          if (!path[0])
            return;

          this.dropText = path[0];
          EventBus.$emit('dll file', path[0]);

        });
      }
    },
    mounted () {

      EventBus.$on('injection', result => this.injectionStatus = result);

      document.addEventListener('dragover', event => event.preventDefault());

      document.addEventListener('drop', event => {

        event.preventDefault();

        this.dropText = event.dataTransfer.files[0].path;
        EventBus.$emit('dll file', event.dataTransfer.files[0].path);

      });

    },
    computed: {
      statusInformer () {
        switch (this.injectionStatus) {
          case InjectionStatus.Success:
            return 'success';
          case InjectionStatus.Failed:
            return 'failed';
        }
      }
    }
  }
</script>

<style lang="scss" scoped>

  .drop {
    cursor: pointer;
    margin-top: 10px;
    color: #fff;
    background: #3b3c4a;
    border: 2px dashed #f62f6d;
    border-radius: 5px;
    width: 100%;
    max-width: 376px;
    padding: 34px 34px;
    transition: .5s all;
  }

  .drop.success {
    border-color: #248232;
  }

  .drop.failed {
    border-color: #f71735;
  }

  .drop-text {
    text-align: center;
    font-weight: 400;
    background: #3b3c4a;
    color: #f62f6d;
    opacity: .8;
  }

</style>
