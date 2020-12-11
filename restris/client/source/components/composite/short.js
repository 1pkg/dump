import React from 'react'
import Drawer from 'material-ui/Drawer'

import Playarea from '~/components/service/playarea'
import Panel from '~/components/service/panel'

export default class extends React.Component {
    state = { drawered: false }

    render() {
        return (
            <div style={{ width: '100%', height: '100%', display: 'flex' }}>
                <Playarea
                    view={this.props.view}
                    over={this.props.over}
                    running={this.props.running}
                    restart={this.props.restart}
                    interact={this.props.interact}
                    toggle={this.props.toggle}
                />
                <Drawer
                    docked={false}
                    width="50%"
                    open={this.state.drawered}
                    onRequestChange={drawered => {
                        this.setState(state => {
                            Object.assign({ state }, { drawered })
                        })
                    }}
                    swipeAreaWidth={null}
                    openSecondary
                    containerStyle={{ display: 'flex' }}
                >
                    <Panel
                        nickname={this.props.nickname}
                        preview={this.props.preview}
                        fps={this.props.fps}
                        rating={this.props.rating}
                        score={this.props.score}
                        over={this.props.over}
                    />
                </Drawer>
            </div>
        )
    }
}
