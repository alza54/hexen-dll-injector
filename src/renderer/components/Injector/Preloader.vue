<template>
  <div :class="{ finished }" id="loader">
    <div id="loaderContainer">
      <img id="logo" src="~@/assets/logo.png" alt="hex-en logo">
    </div>
  </div>
</template>

<script lang="ts">
  export default {
    name: 'preloader',
    data () {
      return {
        finished: false
      }
    },
    mounted () {
      setTimeout(() => this.finished = true, 550);
    }
  }
</script>

<style lang="scss" scoped>

  #loader {
    background: #0b0c1b !important;
    position: fixed;
    top: 0;
    right: 0;
    bottom: 0;
    left: 0;
    display: flex;
    align-items: center;
    justify-content: center;
    z-index: 1005;
    transition: opacity 0.6s linear;
  }

  #loader.finished {
    opacity: 0;
    pointer-events: none;
  }

  #loaderContainer {
    flex: 1;
  }

  #loaderContainer img {
    display: block;
    margin: 0 auto;
    margin-bottom: 50px;
    max-width: 500px;
    opacity: 0;
    transform: scale(0.2);
    animation: enter 1.2s cubic-bezier(0, 1.07, 1, 1) forwards;
  }

  #loaderContainerSpinner {
    display: block;
    margin: 0 auto;
    color: #a88f6d;
    width: 64px;
    height: 64px;
  }

  @keyframes enter {
    20% {
      transform: scale(1.1);
      opacity: 0.7;
    }
    40% {
      opacity: 0.4;
    }
    100% {
      opacity: 1;
      transform: scale(1);
    }
  }

</style>
