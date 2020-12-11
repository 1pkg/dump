import React from 'react'
import RaisedButton from 'material-ui/RaisedButton'
import Left from 'material-ui/svg-icons/hardware/keyboard-arrow-left'
import Rigth from 'material-ui/svg-icons/hardware/keyboard-arrow-right'
import Counterclockwise from 'material-ui/svg-icons/image/rotate-left'
import Сlockwise from 'material-ui/svg-icons/image/rotate-right'
import Boost from 'material-ui/svg-icons/hardware/keyboard-arrow-down'
import Play from 'material-ui/svg-icons/av/play-arrow'
import Restart from 'material-ui/svg-icons/av/replay'

let ActionButton = ({ action, icon, disabled = false }) => {
    return (
        <RaisedButton
            onClick={action}
            icon={React.createElement(icon, {
                style: { flex: 1, width: '100%', height: 'auto' },
            })}
            disableTouchRipple
            disabled={disabled}
            style={{
                flex: 1,
                margin: '0.4em',
                minWidth: 0,
                display: 'flex',
            }}
            buttonStyle={{
                flex: 1,
                height: 'auto',
                display: 'flex',
                flexDirection: 'column',
            }}
            overlayStyle={{ flex: 1, height: 'auto', display: 'flex' }}
        />
    )
}

export default class extends React.Component {
    render() {
        return (
            <div
                style={{
                    flex: 1,
                    display: 'flex',
                    justifyContent: 'space-between',
                }}
            >
                <div style={{ flex: 2, display: 'flex' }}>
                    <ActionButton
                        action={this.props.interact.bind(null, 'move', -1)}
                        icon={Left}
                        disabled={this.props.over || !this.props.running}
                    />
                    <ActionButton
                        action={this.props.interact.bind(null, 'move', 1)}
                        icon={Rigth}
                        disabled={this.props.over || !this.props.running}
                    />
                </div>
                <div style={{ flex: 2, display: 'flex' }}>
                    <ActionButton
                        action={this.props.interact.bind(null, 'rotate', 1)}
                        icon={Counterclockwise}
                        disabled={this.props.over || !this.props.running}
                    />
                    <ActionButton
                        action={this.props.interact.bind(null, 'rotate', -1)}
                        icon={Сlockwise}
                        disabled={this.props.over || !this.props.running}
                    />
                </div>
                <div style={{ flex: 1, display: 'flex' }}>
                    <ActionButton
                        action={this.props.interact.bind(null, 'boost', 1)}
                        icon={Boost}
                        disabled={this.props.over || !this.props.running}
                    />
                </div>
                <div style={{ flex: 1, display: 'flex' }}>
                    <ActionButton action={this.props.toggle} icon={Play} />
                </div>
                <div style={{ flex: 1, display: 'flex' }}>
                    <ActionButton action={this.props.restart} icon={Restart} />
                </div>
            </div>
        )
    }
}
