<template>
  <button @click="inject" id="inject">Inject</button>
</template>

<script lang="ts">

  import EventBus from '../../bus';
  import { InjectionStatus } from '../../enums';

  // Import & Initialise Injector Library
  const Injector = require('../../../../lib/bindings/injector/index');

  const { remote } = require('electron');
  const { BrowserWindow } = remote;
  const debugWindow = BrowserWindow.getAllWindows()[1];

  const path = require('path');

  // Bind "log" callback for log handling
  Injector.on('log', function (type, message, data) {
    if (debugWindow) {
      debugWindow.webContents.send('debug data', { type, message, data });
    }
  });

  export default {
    name: 'inject-button',
    methods: {
      inject () {

        if (!this.processId) {
          return;
        }

        if (!this.dllPath) {
          EventBus.$emit('injection', InjectionStatus.Failed);
          return;
        }

        const dll = path.parse(this.dllPath);
        if (dll.ext !== '.dll') {
          EventBus.$emit('injection', InjectionStatus.Failed);
          return;
        }

        if (Injector.inject(this.processId, this.dllPath)) {
          EventBus.$emit('injection', InjectionStatus.Success);
        } else {
          EventBus.$emit('injection', InjectionStatus.Failed);
        }

      }
    },
    data () {
      return {
        dllPath: null,
        processId: 0
      }
    },
    mounted () {
      EventBus.$on('process', process => this.processId = process.pid);
      EventBus.$on('dll file', path => this.dllPath = path);
    }
  }

</script>

<style lang="scss" scoped>

  #inject {
    cursor: pointer;
    border: none;
    padding: 0 30px;
    will-change: opacity, color;
    white-space: nowrap;
    text-overflow: ellipsis;
    display: block;
    font-weight: 500;
    text-transform: uppercase;
    background: #f62f6d;
    width: 100%;
    max-width: 450px;
    color: #fff;
    border-radius: 0;
    margin-top: 30px;
    font-size: 1.2rem;
    line-height: 3rem;
    transition: all .2s ease-in-out;
    text-shadow: 0 0 32px black;
  }

  #inject:hover {
    transform: scale(1.05);
  }

  #inject {
    // Find better font..
    font-size: 1.4em;
  }

</style>
