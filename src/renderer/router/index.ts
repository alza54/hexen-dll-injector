import Vue from 'vue'
import Router from 'vue-router'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'hexen-dll-injector',
      component: require('@/components/Injector').default
    },
    {
      path: '/debug',
      name: 'debug',
      component: require('@/components/Debug').default
    },
    {
      path: '*',
      redirect: '/'
    }
  ]
})
