import React from 'react'

import View from '~/components/playarea/view'
import Control from '~/components/playarea/control'

export default class extends React.Component {
    render() {
        return (
            <div
                style={{
                    flex: 1,
                    display: 'flex',
                    flexDirection: 'column',
                }}
            >
                <View view={this.props.view} over={this.props.over} />
                <Control
                    over={this.props.over}
                    running={this.props.running}
                    interact={this.props.interact}
                    restart={this.props.restart}
                    toggle={this.props.toggle}
                />
            </div>
        )
    }
}
