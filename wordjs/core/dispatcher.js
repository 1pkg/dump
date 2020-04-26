// systems
var __DISPATCHER__ = null

function createARGS() {
    var arr = []
    for (var i = 0; i < arguments.length; i++) arr.push(arguments[i])
    return arr
}

var register = {
    scripts: undefined,
    styles: undefined,
    DOMs: undefined,
    pages: undefined,
}

// scripts
function script(arg) {
    this.name = arg[0]
    this.type = arg[1]
    this.parrentDirectory = arg[2] || 'core'

    var url = null

    this.dom = null
}
script.initDOM = function(element) {
    element.url = element.parrentDirectory + '/'

    if (element.type != undefined) {
        element.url += element.type + '/'
        element.url += 'script/'
    }

    element.url += element.name + '.js'

    element.dom = document.createElement('script')
    element.dom.type = 'text/javascript'
    element.dom.src = element.url
}
script.appendDOM = function(element) {
    document.head.appendChild(element.dom)
}

// styles
function style(arg) {
    this.name = arg[0]
    this.type = arg[1]
    this.parrentDirectory = arg[2] || 'core'

    var url = null

    this.dom = null
}
style.initDOM = function(element) {
    element.url = element.parrentDirectory + '/'

    if (element.type != undefined) {
        element.url += element.name + '/'
        element.url += 'style/'
        element.url += element.type + '.css'
    } else element.url += element.name + '.css'

    element.dom = document.createElement('link')
    element.dom.rel = 'stylesheet'
    element.dom.href = element.url
}
style.appendDOM = function(element) {
    document.head.appendChild(element.dom)
}

// dom object
function DOM(arg) {
    this.tag = arg[0]
    this.id = arg[1] || ''
    this.classname = arg[2] || ''
    this.upperContainer = arg[3] || document.getElementById('__main__')
    this.inner = arg[4] || ''
    this.title = arg[5] || ''

    this.dom = null
}
DOM.initDOM = function(element) {
    element.dom = document.createElement(element.tag)

    element.dom.id = element.id
    element.dom.className = element.classname
    element.dom.innerHTML = element.inner
    element.dom.title = element.title
}
DOM.appendDOM = function(element) {
    element.upperContainer.appendChild(element.dom)
}

// dom container
function DOMContainer(type) {
    var elementSheets = []
    this.typeOf = type

    this.init = function() {
        elementSheets.forEach(this.init.initDOM)
        elementSheets.forEach(this.init.appendDOM)
    }

    this.init.initDOM = window[this.typeOf].initDOM
    this.init.appendDOM = window[this.typeOf].appendDOM

    this.setElement = function(params) {
        var obj = new window[this.typeOf](params)
        elementSheets.push(obj)
    }

    this.getElement = function(index) {
        if (index == undefined) return elementSheets[0]
        if (elementSheets.length > index) return elementSheets[index]
    }

    this.getLastElement = function() {
        return elementSheets[elementSheets.length - 1]
    }

    this.deleteElement = function(index, dom) {
        if (index == undefined) index = 0
        if (dom == undefined) dom = document.getElementById('__main__')

        if (elementSheets.length > index) {
            dom.removeChild(elementSheets[index].dom)
            delete elementSheets[index]
        }
    }

    this.clearArr = function(index, dom) {
        for (var i = 0; elementSheets.length >= i; i++) elementSheets.pop()
    }
}

// initScripts
function initScripts(arg) {
    var currentScripts = new DOMContainer('script')
    currentScripts.setElement(createARGS('splitter'))
    currentScripts.setElement(createARGS('JQ'))
    currentScripts.init()

    function check() {
        if (
            typeof window.__SPLITTER__ != undefined &&
            typeof window.__JQ__ != undefined
        ) {
            register.scripts = true
            clearInterval(timer)
        }
    }
    var timer = setInterval(check, 100)

    return currentScripts
}

// initStyles
function initStyles(arg) {
    var currentStyles = new DOMContainer('style')
    currentStyles.setElement(createARGS('shell', 'classic'))

    if (arg == 'modify') currentStyles.setElement(createARGS('page', 'modify'))
    else if (arg == 'classic')
        currentStyles.setElement(createARGS('page', 'classic'))

    currentStyles.setElement(createARGS('menu', 'classic'))
    currentStyles.init()

    function check() {
        if (document.body != null) {
            register.styles = true
            clearInterval(timer)
        }
    }
    var timer = setInterval(check, 100)

    return currentStyles
}

// initDOMs
function initDOMs(arg) {
    var currentDOMS = new DOMContainer('DOM')
    currentDOMS.setElement(createARGS('img', '__pageIMG__'))
    currentDOMS.setElement(createARGS('div', null, '__separator__'))
    currentDOMS.init()

    function check() {
        if (document.getElementById('__pageIMG__') != null) {
            register.DOMs = true
            clearInterval(timer)
        }
    }

    var timer = setInterval(check, 100)

    return currentDOMS
}

function menuBlocks() {
    var menu = new DOMContainer('DOM')
    menu.setElement(createARGS('nav', undefined, '__menu__'))
    menu.init()

    var menuUl = new DOMContainer('DOM')
    menuUl.setElement(
        createARGS('ul', undefined, undefined, menu.getElement().dom),
    )
    menuUl.init()

    var menuLi = new DOMContainer('DOM')
    menuLi.setElement(
        createARGS('li', undefined, undefined, menuUl.getElement().dom),
    )
    menuLi.init()

    var menuDropDown = new DOMContainer('DOM')
    menuDropDown.setElement(
        createARGS('div', undefined, undefined, menuLi.getElement().dom, ''),
    )
    menuDropDown.setElement(
        createARGS('ul', undefined, undefined, menuLi.getElement().dom),
    )
    menuDropDown.init()

    var tempEl = document.createElement('div')
    tempEl.className = 'tring'
    menuDropDown.getElement().dom.appendChild(tempEl)

    return menuDropDown
}

function initPages(arg) {
    var elements = document.getElementsByClassName('container')

    var page = new DOMContainer('DOM')
    var contentContainer = new DOMContainer('DOM')
    var textContainer = new DOMContainer('DOM')
    var parrent = menuBlocks()
    var menuContainerLi = new DOMContainer('DOM')
    var menuContainerA = new DOMContainer('DOM')
    var len = elements.length

    for (var i = 0; elements.length != 0; ) {
        var objPage = split(
            '<h4>' +
                elements.item(i).id +
                '</h4>\\n' +
                elements.item(i).innerHTML,
        )
        menuContainerLi.setElement(
            createARGS('li', undefined, undefined, parrent.getElement(1).dom),
        )
        menuContainerLi.init()
        menuContainerA.setElement(
            createARGS(
                'a',
                undefined,
                undefined,
                menuContainerLi.getElement().dom,
                elements.item(i).id,
            ),
        )
        menuContainerA.init()
        menuContainerA.getElement().dom.href = '#page' + elements.length + '0'

        for (var j = 0; j < objPage.pageCount; j++)
            page.setElement(
                createARGS('div', 'page' + elements.length + j, 'page'),
            )

        page.init()

        for (var j = 0; j < objPage.pageCount; j++)
            contentContainer.setElement(
                createARGS(
                    'div',
                    undefined,
                    'contentContainer',
                    page.getElement(j).dom,
                ),
            )

        contentContainer.init()

        for (var j = 0; j < objPage.pageCount; j++)
            textContainer.setElement(
                createARGS(
                    'div',
                    undefined,
                    'textContainer',
                    contentContainer.getElement(j).dom,
                    objPage.strRes[j],
                ),
            )

        textContainer.init()

        textContainer.clearArr(),
            contentContainer.clearArr(),
            page.clearArr(),
            menuContainerLi.clearArr(),
            menuContainerA.clearArr()

        document.body.removeChild(elements.item(i))
    }

    register.pages = true
}

function saveContainer(container) {
    saveContainer.containers[container.id] = container.innerHTML
}

function initPage1(arg) {
    var elements = document.getElementsByClassName('container')

    var page = new DOMContainer('DOM')
    var contentContainer = new DOMContainer('DOM')
    var textContainer = new DOMContainer('DOM')
    var len = elements.length

    if (elements.length != 0) {
        var parrent = menuBlocks()
        var menuContainerLi = new DOMContainer('DOM')
        var menuContainerA = new DOMContainer('DOM')
    }

    for (var i = 0; elements.length != 0; ) {
        saveContainer(elements.item(i))

        menuContainerLi.setElement(
            createARGS('li', undefined, undefined, parrent.getElement(1).dom),
        )
        menuContainerLi.init()

        menuContainerA.setElement(
            createARGS(
                'a',
                elements.item(i).id,
                undefined,
                menuContainerLi.getElement().dom,
                elements.item(i).id,
            ),
        )
        menuContainerA.init()

        menuContainerA.getElement().dom.addEventListener('click', function() {
            initPage1(saveContainer.containers[this.id])
        })

        document.body.removeChild(elements.item(i))
        menuContainerLi.clearArr(), menuContainerA.clearArr()
    }

    var text = document.getElementsByClassName('textContainer')[0]
    var contect = document.getElementsByClassName('contentContainer')[0]
    var pag = document.getElementsByClassName('page')[0]
    var main = document.getElementById('__main__')

    if (pag != undefined) {
        main.removeChild(pag)
    }

    var str = split1Page(arg)

    page.setElement(createARGS('div', undefined, 'page'))
    page.init()

    contentContainer.setElement(
        createARGS('div', undefined, 'contentContainer', page.getElement().dom),
    )
    contentContainer.init()

    textContainer.setElement(
        createARGS(
            'div',
            undefined,
            'textContainer',
            contentContainer.getElement().dom,
            str,
        ),
    )
    textContainer.init()

    register.pages = true
}

// main
;(function() {
    var styles, scripts, DOMs, pages, main

    function DOMTimer() {
        if (register.styles && register.scripts) {
            clearInterval(DOMTime)
            main = document.createElement('div')
            main.id = '__main__'
            document.body.appendChild(main)
            DOMs = initDOMs()
        }
    }

    function pageTimer() {
        if (register.DOMs) {
            var styleD = document.getElementById('style').innerHTML

            if (styleD == 'modify') {
                clearInterval(pageTime)
                saveContainer.containers = {}
                initPage1(
                    document.getElementsByClassName('container')[0].innerHTML,
                )
            } else if (styleD == 'classic') {
                clearInterval(pageTime)
                initPages()
            }
            document.body.removeChild(document.getElementById('style'))
        }
    }

    function showTimer() {
        if (register.pages) {
            clearInterval(showTime)
            main.style.visibility = 'visible'
            main.style.overflow = 'auto'
        }
    }

    styles = initStyles(document.getElementById('style').innerHTML)
    scripts = initScripts()

    var DOMTime = setInterval(DOMTimer, 100)
    var pageTime = setInterval(pageTimer, 100)
    var showTime = setInterval(showTimer, 100)
})()
