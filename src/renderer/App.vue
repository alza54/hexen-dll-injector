<template>
  <div id="app">
    <router-view></router-view>
  </div>
</template>

<script lang="ts">
  export default {
    name: 'hexen-dll-injector'
  }
</script>

<style lang="scss">

  // Make images non-draggable and non-selectable
  img {
    user-select: none;
    -webkit-user-drag: none;
  }

  button {
    -webkit-app-region: no-drag;
  }

  // No outlines
  *:focus {
    outline: none !important;
  }

  // No underlines
  a {
    text-decoration: none;
  }

  * {
    user-select: none;
  }

</style>
