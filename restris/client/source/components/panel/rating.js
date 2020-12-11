import React from 'react'
import { List, ListItem } from 'material-ui/List'
import * as Colors from 'material-ui/styles/colors'
import Divider from 'material-ui/Divider'

export default class extends React.Component {
    render() {
        return (
            <List
                style={{
                    flex: 1,
                    display: 'flex',
                    justifyContent: 'space-evenly',
                    flexDirection: 'column',
                    backgroundColor: Colors.grey800,
                    padding: 0,
                }}
            >
                <ListItem
                    style={{ fontSize: '1.2em' }}
                    innerDivStyle={{
                        display: 'flex',
                        justifyContent: 'space-between',
                        padding: '0.3em',
                        lineHeight: 'auto',
                    }}
                >
                    <span>Nickname</span>
                    <span>Score</span>
                </ListItem>
                <Divider />
                {Object.keys(this.props.rating).map(nickname => {
                    return (
                        <ListItem
                            key={nickname}
                            style={{ fontSize: '0.6em' }}
                            innerDivStyle={{
                                display: 'flex',
                                justifyContent: 'space-between',
                                padding: '0.3em',
                                lineHeight: 'auto',
                            }}
                        >
                            <span>{nickname}</span>
                            <span>{this.props.rating[nickname]}</span>
                        </ListItem>
                    )
                })}
            </List>
        )
    }
}
