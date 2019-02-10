<template>
  <div id="app">
    <preloader></preloader>
    <title-bar></title-bar>
    <logo></logo>
    <process-select></process-select>
    <drop-area></drop-area>
    <inject-button></inject-button>
    <debug-mode></debug-mode>
    <footer-info></footer-info>
  </div>
</template>

<script lang="ts">

  import Preloader from '@/components/Injector/Preloader'
  import TitleBar from '@/components/Injector/TitleBar'
  import Logo from '@/components/Injector/Logo'
  import ProcessSelect from '@/components/Injector/ProcessSelect'
  import DropArea from '@/components/Injector/DropArea'
  import InjectButton from '@/components/Injector/InjectButton'
  import DebugMode from '@/components/Injector/DebugMode'
  import FooterInfo from '@/components/Injector/FooterInfo'

  export default {
    name: 'injector-window',
    components: {
      Preloader, TitleBar, Logo, ProcessSelect,
      DropArea, InjectButton, DebugMode, FooterInfo
    }
  }

</script>

<style lang="scss" scoped>

  $gray: #8f95a0;
  $background: #0b0c1b;

  #app {
    // flex!!
    display: flex;
    // Never display scrollbar
    overflow: hidden;
    // Make edges rounded
    border-radius: 7px;
    position: fixed;
    top: 0;
    right: 0;
    bottom: 0;
    left: 0;
    // Styling
    background: $background;
    color: $gray;
    font-family: Circular, Roboto, Helvetica, Arial, sans-serif;
    font-weight: 400;
    // Font Smoothing
    -webkit-font-smoothing: antialiased;
  }

  #app {
    justify-content: center;
    align-items: center;
    flex-direction: column;
    flex: 1;
  }

</style>
