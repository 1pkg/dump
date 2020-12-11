import React from 'react'
import Chip from 'material-ui/Chip'

let Field = ({ label, value }) => {
    return (
        <Chip
            style={{ display: 'flex', margin: '0.1em' }}
            labelStyle={{
                flex: 1,
                display: 'flex',
                justifyContent: 'space-between',
                fontSize: '0.8em',
                padding: '0.3em',
                lineHeight: 'auto',
            }}
        >
            <span style={{ fontWeight: 'bold' }}>{label}</span>
            <span style={{ whiteSpace: 'pre' }}> {value} </span>
        </Chip>
    )
}

export default class extends React.Component {
    render() {
        return (
            <div
                style={{
                    display: 'flex',
                    flexDirection: 'column',
                }}
            >
                <div
                    style={{
                        display: 'flex',
                        justifyContent: 'space-between',
                        marginBottom: '0.5em',
                    }}
                >
                    <Field label="NICKNAME:" value={this.props.nickname} />
                    <Field
                        label="FPS:"
                        value={Number(this.props.fps).toFixed(2)}
                    />
                </div>
                <div
                    style={{
                        display: 'flex',
                        justifyContent: 'space-between',
                    }}
                >
                    <Field
                        label="STATUS:"
                        value={this.props.over ? 'over' : 'running'}
                    />
                    <Field label="SCORE:" value={this.props.score} />
                </div>
            </div>
        )
    }
}
