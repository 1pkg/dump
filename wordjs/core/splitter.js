var __SPLITTER__ = null
function word(arg) {
    this.text = arg[0]
    this.start = arg[1]
    this.end = arg[2] || arg[1]
    this.posit = arg[3]
}

function transfer(word) {
    var vowel = new String('аеёиоуыэюя')
    var voiced = new String('бвгджзлмнрхцчшщ')
    var deaf = new String('кпстф')
    var brief = new String('й')
    var other = new String('ьъ')
    var cons = new String('бвгджзйклмнпрстфхцчшщ')

    return getSeparatedString(word)

    function isNotLastSep(remainStr) {
        var is = false
        for (var i = 0; i < remainStr.length; i++) {
            if (vowel.indexOf(remainStr.substr(i, 1)) != -1) {
                is = true
                break
            }
        }
        return is
    }

    function getSeparatedString(s) {
        function addSep() {
            sepArr.push(tmpS)
            tmpS = ''
        }

        var tmpL = new String()
        var tmpS = new String()
        var sepArr = new Array()
        for (var i = 0; i < s.length; i++) {
            tmpL = s.substr(i, 1)
            tmpS += tmpL

            if (
                i != 0 &&
                i != s.length - 1 &&
                brief.indexOf(tmpL) != -1 &&
                isNotLastSep(s.substr(i + 1, s.length - i + 1))
            ) {
                addSep()
                continue
            }

            if (
                i < s.length - 1 &&
                vowel.indexOf(tmpL) != -1 &&
                vowel.indexOf(s.substr(i + 1, 1)) != -1
            ) {
                addSep()
                continue
            }

            if (
                i < s.length - 2 &&
                vowel.indexOf(tmpL) != -1 &&
                cons.indexOf(s.substr(i + 1, 1)) != -1 &&
                vowel.indexOf(s.substr(i + 2, 1)) != -1
            ) {
                addSep()
                continue
            }

            if (
                i < s.length - 2 &&
                vowel.indexOf(tmpL) != -1 &&
                deaf.indexOf(s.substr(i + 1, 1)) != -1 &&
                cons.indexOf(s.substr(i + 2, 1)) != -1 &&
                isNotLastSep(s.substr(i + 1, s.length - i + 1))
            ) {
                addSep()
                continue
            }

            if (
                i > 0 &&
                i < s.length - 1 &&
                voiced.indexOf(tmpL) != -1 &&
                vowel.indexOf(s.substr(i - 1, 1)) != -1 &&
                vowel.indexOf(s.substr(i + 1, 1)) == -1 &&
                other.indexOf(s.substr(i + 1, 1)) == -1 &&
                isNotLastSep(s.substr(i + 1, s.length - i + 1))
            ) {
                addSep()
                continue
            }

            if (
                i < s.length - 1 &&
                other.indexOf(tmpL) != -1 &&
                (vowel.indexOf(s.substr(i + 1, 1)) == -1 ||
                    isNotLastSep(s.substr(0, i)))
            ) {
                addSep()
                continue
            }
        }

        sepArr.push(tmpS)
        return sepArr.join('\xAD')
    }
}

function parseStr(str) {
    var res = []
    var weight = 0
    var one = '',
        position = 0,
        symb

    for (var i = 0; i <= str.length; i++) {
        symb = str.charAt(i)

        if (i == str.length)
            res.push(
                new word(createARGS(transfer(one), position, i - 1, weight)),
            )
        else if (symb == ' ') {
            if (one != '')
                res.push(
                    new word(
                        createARGS(transfer(one), position, i - 1, weight),
                    ),
                )

            res.push(new word(createARGS(' ', i, i + 1, weight)))

            position = i
            one = ''
        } else {
            one += symb
        }
        weight++
    }
    return res
}

function join(arr, weight) {
    var str = ''
    var curWeigth = 0

    while (curWeigth < weight && split.i < arr.length) {
        str += arr[split.i].text
        curWeigth += arr[split.i].end - arr[split.i].start
        split.i++
    }
    return str
}

function cutTheWorld(str) {
    var res

    var buf = ''
    for (var i = str.length - 1; i >= 0; i--) {
        symb = str.charAt(i)

        if (symb == ' ') {
            if (buf == '') res = str.substr(0, i)
            else res = str.substr(0, i + 1)
            break
        }

        buf += symb
    }
    return res
}

function reParse(string) {
    var str = string

    str = str.replace(/(\r\n|\n|\r|\t)/gm, '')
    str = str.replace(/[.]/gm, '. ')
    str = str.replace(/[  ]/gm, ' ')
    str = str.replace(/(\\t)/gm, '&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp')
    str = str.replace(/(\\n)/gm, '&nbsp\n&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp')

    return str
}

function split1Page(arg) {
    var str = reParse(arg)
    var words = parseStr(str)

    str = ''
    function callback(item) {
        str += item.text
    }

    words.forEach(callback)
    return str
}

function split(arg) {
    var res = {}

    var str = reParse(arg)

    var contentContainer = new DOMContainer('DOM')
    var textContainer = new DOMContainer('DOM')

    contentContainer.setElement(
        createARGS('div', 'fakecontentContainer', 'contentContainer'),
    )
    contentContainer.init()
    contentContainer.getElement().dom.style.visibility = 'hidden'

    textContainer.setElement(
        createARGS(
            'div',
            'fakeContainer',
            'textContainer',
            contentContainer.getElement().dom,
            str,
        ),
    )
    textContainer.init()
    textContainer.getElement().dom.style.visibility = 'hidden'
    textContainer.getElement().dom.style.paddingTop = '0pt'
    textContainer.getElement().dom.style.marginBottom = '0pt'

    var classicSize = textContainer.getElement().dom.offsetHeight
    textContainer.getElement().dom.style.height = 'auto'
    var currentSize = textContainer.getElement().dom.offsetHeight

    var words = parseStr(str)

    var maxWeight = words[words.length - 1].posit

    var temp = 0
    function callback(item) {
        temp += item.end - item.start
    }
    words.forEach(callback)

    var koef = currentSize / classicSize
    var rial = maxWeight / koef
    var unRial = maxWeight - rial * Math.floor(koef)

    res.pageCount = Math.ceil(koef)

    split.i = 0

    res.pageCount = Math.ceil(koef)
    res.strRes = []

    var strRes
    for (var j = 0; j < res.pageCount; j++) {
        textContainer.getElement().dom.innerHTML = ''

        if (j == res.pageCount - 1)
            textContainer.getElement().dom.innerHTML = join(words, unRial)
        else textContainer.getElement().dom.innerHTML = join(words, rial)

        strRes = textContainer.getElement().dom.innerHTML
        if (textContainer.getElement().dom.offsetHeight <= classicSize) {
            while (
                textContainer.getElement().dom.offsetHeight <= classicSize &&
                split.i < words.length
            ) {
                textContainer.getElement().dom.innerHTML += words[split.i].text

                if (textContainer.getElement().dom.offsetHeight <= classicSize)
                    strRes = textContainer.getElement().dom.innerHTML
                else break

                split.i++
            }
        } else {
            while (
                textContainer.getElement().dom.offsetHeight >= classicSize &&
                split.i > 0
            ) {
                textContainer.getElement().dom.innerHTML = cutTheWorld(
                    textContainer.getElement().dom.innerHTML,
                )

                strRes = textContainer.getElement().dom.innerHTML

                split.i--
            }
        }
        res.strRes.push(strRes)
    }

    textContainer.deleteElement(undefined, contentContainer.getElement().dom)
    contentContainer.deleteElement()

    return res
}
