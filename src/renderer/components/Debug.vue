<template>
  <div id="debug-window">
    <div id="logo-wrap">
      <logo></logo>
      <p>console</p>
    </div>
    <div id="console">
      <div :class="log.type" v-for="log in logs">
        {{ log.message }}
      </div>
    </div>
  </div>
</template>

<script lang="ts">

  import Logo from '@/components/Injector/Logo';
  import EventBus from '../bus';

  const { ipcRenderer } = require('electron');

  export default {
    name: 'debug-console',
    components: { Logo },
    data () {
      return {
        logs: []
      }
    },
    mounted () {
      ipcRenderer.on('debug data', (event, data) => {
        this.logs.push(data);
      });
    },
    beforeCreate () {
      document.title = 'HEX-EN Injector - Debug Console';
      document.body.className = 'debug';
    }
  }

</script>

<style lang="scss">

  body.debug {
    font: 11pt/1.25 Monaco, monospace;
    background: #0b0c1b;
    color: #fff;
    margin: 0;
    padding: 30px 10px;
  }

  body.debug #logo, body.debug #logo-wrap p {
    display: block;
    margin: 0 auto;
  }

  body.debug #logo-wrap p {
    text-align: center;
    position: relative;
    top: 10px;
  }

</style>

<style lang="scss" scoped>

  .debug { color: Snow; }
  .success  { color: LawnGreen; }
  .warn  { color: GoldenRod; }
  .error { color: LightCoral; }

  #console {
    opacity: .9;
    background: rgba(0, 0, 0, .75);
    width: 75%;
    height: 300px;
    overflow: auto;
    margin: 30px auto;
    padding-left: 20px;
    padding-top: 20px;
  }

  #console::-webkit-scrollbar { width: 6px; height: 3px;}
  #console::-webkit-scrollbar-button {  background-color: transparent; }
  #console::-webkit-scrollbar-track {  background-color: transparent;}
  #console::-webkit-scrollbar-track-piece { background-color: transparent;}
  #console::-webkit-scrollbar-thumb { height: 50px; background-color: #333; border-radius: 3px;}
  #console::-webkit-scrollbar-corner { background-color: transparent;}
  #console::-webkit-resizer { background-color: transparent;}

</style>
