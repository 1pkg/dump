export default class {
    intervals = {}

    start(name, action, interval = 200) {
        this.stop(name)
        setTimeout(() => {
            this.intervals[name] = setInterval(action, interval)
        })
    }

    stop(name) {
        if (name in this.intervals) {
            clearInterval(this.intervals[name])
        }
    }
}
