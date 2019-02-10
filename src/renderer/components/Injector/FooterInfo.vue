<template>
  <div class="footer-info">
    Copyright &copy; 2019; <a href="//shellcode.team">shellcode.team</a>
  </div>
</template>

<script lang="ts">

  const { shell } = require('electron');

  export default {
    name: 'footer-info',
    mounted () {
      document.addEventListener('click', event => {
        const target = event.target as any;
        if (target.tagName === 'A' && target.href.startsWith('http')) {
          event.preventDefault();
          shell.openExternal(target.href);
        }
      })
    }
  }

</script>

<style lang="scss" scoped>

  .footer-info {
    max-width: 350px;
    margin-top: 20px;
    font-size: 1rem;
  }

  .footer-info a {
    color: #f62f6d;
  }

</style>
