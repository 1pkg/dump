import React from 'react'
import * as Redux from 'react-redux'
import Detect from 'ismobilejs'

import Runner from '~/utils/runner'
import Fps from '~/utils/fps'
import Initialize from '~/actions/initialize'
import Interact from '~/actions/interact'
import Update from '~/actions/update'
import View from '~/actions/view'
import * as Constants from '~/constants'
import Full from './composite/full'
import Short from './composite/short'
import Initial from './composite/initial'

class Main extends React.Component {
    runner = new Runner()
    fps = new Fps()
    state = { fps: 0, running: false }

    componentDidMount() {
        if (this.props.id) {
            this.view()
        }
    }

    resume() {
        this.runner.start(Constants.ACTION_UPDATE, this.update.bind(this))
        this.runner.start(Constants.ACTION_VIEW, this.view.bind(this))
        this.setState(state => {
            return {
                fps: state.fps,
                running: true,
            }
        })
    }

    pause() {
        this.runner.stop(Constants.ACTION_UPDATE)
        this.runner.stop(Constants.ACTION_VIEW)
        this.setState(state => {
            return {
                fps: state.fps,
                running: false,
            }
        })
    }

    toggle() {
        if (this.state.running) {
            this.pause()
        } else {
            this.resume()
        }
    }

    restart() {
        Initialize(this.props.nickname, this.props.id).then(state => {
            this.props.dispatch(state)
            this.resume()
        })
    }

    initialize(nickname) {
        Initialize(nickname).then(state => {
            this.props.dispatch(state)
            this.resume()
        })
    }

    interact(action, direction) {
        Interact(this.props.id, action, direction).then(state => {})
    }

    update() {
        Update(this.props.id).then(state => {
            this.props.dispatch(state)
            if (state.data.over) {
                this.pause()
                this.view()
            }
        })
    }

    view() {
        View(this.props.id).then(state => {
            this.props.dispatch(state)
            let fps = this.fps.count()
            if (fps != this.state.fps) {
                this.setState(state => {
                    return {
                        running: state.running,
                        fps,
                    }
                })
            }
        })
    }

    render() {
        if (!this.props.id) {
            return <Initial initialize={this.initialize.bind(this)} />
        }

        return Detect.any ? (
            <Short
                nickname={this.props.nickname}
                id={this.props.id}
                view={this.props.view}
                preview={this.props.preview}
                fps={this.state.fps}
                running={this.state.running}
                rating={this.props.rating}
                score={this.props.score}
                over={this.props.over}
                restart={this.restart.bind(this)}
                interact={this.interact.bind(this)}
                toggle={this.toggle.bind(this)}
            />
        ) : (
            <Full
                nickname={this.props.nickname}
                id={this.props.id}
                view={this.props.view}
                preview={this.props.preview}
                fps={this.state.fps}
                running={this.state.running}
                rating={this.props.rating}
                score={this.props.score}
                over={this.props.over}
                restart={this.restart.bind(this)}
                interact={this.interact.bind(this)}
                toggle={this.toggle.bind(this)}
            />
        )
    }
}

export default Redux.connect((state, dispatch) => {
    return { ...state, dispatch }
})(Main)
