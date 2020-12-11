import React from 'react'
import { Tabs, Tab } from 'material-ui/Tabs'
import * as Colors from 'material-ui/styles/colors'

import Status from '~/components/panel/status'
import Rating from '~/components/panel/rating'
import Preview from '~/components/panel/preview'
import Footer from '~/components/panel/footer'

export default class extends React.Component {
    render() {
        return (
            <div
                style={{
                    flex: 1,
                    display: 'flex',
                    flexDirection: 'column',
                    justifyContent: 'space-between',
                }}
            >
                <Status
                    nickname={this.props.nickname}
                    score={this.props.score}
                    over={this.props.over}
                    fps={this.props.fps}
                />
                <Tabs
                    style={{ flex: 0.3 }}
                    contentContainerStyle={{ height: '100%' }}
                    initialSelectedIndex={1}
                    tabTemplateStyle={{ height: '100%', display: 'flex' }}
                >
                    <Tab
                        buttonStyle={{
                            backgroundColor: Colors.grey800,
                            color: 'white',
                            fontSize: '0.8em',
                            height: '2em',
                        }}
                        label="Preview"
                    >
                        <Preview
                            view={this.props.preview}
                            over={this.props.over}
                        />
                    </Tab>
                    <Tab
                        buttonStyle={{
                            backgroundColor: Colors.grey800,
                            color: 'white',
                            fontSize: '0.8em',
                            height: '2em',
                        }}
                        label="Rating"
                    >
                        <Rating rating={this.props.rating} />
                    </Tab>
                </Tabs>
                <Footer />
            </div>
        )
    }
}
