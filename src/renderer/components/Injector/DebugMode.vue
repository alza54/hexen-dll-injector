<template>
  <div id="debug-mode" @click="displayDebug">
    Debug Mode
  </div>
</template>

<script lang="ts">

  const { remote } = require('electron');
  const { BrowserWindow } = remote;

  const debugWindow = BrowserWindow.getAllWindows()[1];

  export default {
    name: 'debug-mode',
    methods: {
      displayDebug () {
        debugWindow && debugWindow.show();
      }
    }
  }

</script>

<style lang="scss" scoped>

  #debug-mode {
    position: absolute;
    right: 15px;
    bottom: 15px;
    font-size: 12px;
    cursor: pointer;
  }

</style>
