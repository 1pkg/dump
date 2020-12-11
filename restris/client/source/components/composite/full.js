import React from 'react'

import Playarea from '~/components/service/playarea'
import Panel from '~/components/service/panel'

export default class extends React.Component {
    render() {
        return (
            <div style={{ width: '100%', height: '100%', display: 'flex' }}>
                <div
                    style={{
                        flex: 8,
                        display: 'flex',
                    }}
                >
                    <Playarea
                        view={this.props.view}
                        over={this.props.over}
                        running={this.props.running}
                        restart={this.props.restart}
                        interact={this.props.interact}
                        toggle={this.props.toggle}
                    />
                </div>
                <div
                    style={{
                        flex: 2,
                        display: 'flex',
                        marginLeft: '0.5em',
                        marginRight: '0.5em',
                    }}
                >
                    <Panel
                        nickname={this.props.nickname}
                        preview={this.props.preview}
                        fps={this.props.fps}
                        rating={this.props.rating}
                        score={this.props.score}
                        over={this.props.over}
                    />
                </div>
            </div>
        )
    }
}
