export default class {
    timestamp = null
    ticks = 0

    count() {
        let fps = 0
        if (++this.ticks === 10) {
            fps = this.ticks / ((Date.now() - this.timestamp) / 1000)
            this.ticks = 0
            this.timestamp = Date.now()
        }
        return fps
    }
}
