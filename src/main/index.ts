import { app, BrowserWindow } from 'electron'

/**
 * Set `__static` path to static files in production
 * https://simulatedgreg.gitbooks.io/electron-vue/content/en/using-static-assets.html
 */
if (process.env.NODE_ENV !== 'development') {
  (global as any).__static = require('path').join(__dirname, '/static').replace(/\\/g, '\\\\')
}

let mainWindow
const winURL = process.env.NODE_ENV === 'development'
  ? `http://localhost:9080`
  : `file://${__dirname}/index.html`

let debugWindow
const debugURL = process.env.NODE_ENV === 'development'
  ? `http://localhost:9080/#/debug`
  : `file://${__dirname}/index.html#debug`

if (process.platform !== 'win32') {
  throw 'Only win32 is supported.'
}

function createWindow () {
  /**
   * Initial window options
   */
  mainWindow = new BrowserWindow({
    width: 600,
    height: 450,
    frame: false,
    transparent: true,
    resizable: false,
    maximizable: false,
    fullscreenable: false
  })

  debugWindow = new BrowserWindow({
    width: 800,
    height: 650,
    show: false
  })

  mainWindow.loadURL(winURL)
  debugWindow.loadURL(debugURL)

  debugWindow.on('close', e => {
    e.preventDefault()
    debugWindow.hide()
  })

  mainWindow.on('closed', () => {
    debugWindow.removeAllListeners('close')
    debugWindow.close()
    mainWindow = null
  })

  debugWindow.on('closed', () => {
    debugWindow = null
  })

}

app.on('ready', createWindow)

app.on('window-all-closed', () => {
  // On OS X it is common for applications and their menu bar
  // to stay active until the user quits explicitly with Cmd + Q
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  // On OS X it's common to re-create a window in the app when the
  // dock icon is clicked and there are no other windows open.
  if (mainWindow === null) {
    createWindow()
  }
})
