const Keeper = require('./keeper.js')
const Wall = require('./wall.js')

let wall = new Wall(new Keeper())
// play with parse arguments to teach nn better
wall.parse([
    { domain: 'mudakoff', index: 0.25 },
    { domain: 'mudachyo', index: 0.2 },
    { domain: 'mnogoanekdot', index: 0.2 },
    { domain: 'onlyorly', index: 0.2 },
    { domain: 'super_cutting', index: 0.15 },
    { domain: 'pikabu', index: 0.45 },
    { domain: 'ru2ch', index: 0.6 },
    { domain: '4ch', index: 0.55 },
    { domain: 'lurkopub_alive', index: 0.7 },
    { domain: 'thelurk', index: 0.6 },
    { domain: 'hatethefrench', index: 0.7 },
    { domain: 'sh_ring', index: 0.3 },
    { domain: 'academyofman', index: 0.2 },
    { domain: 'ifun', index: 0.2 },
    { domain: 'smeyaka', index: 0.15 },
    { domain: 'fuck_humor', index: 0.15 },
    { domain: 'oroom', index: 0.15 },
    { domain: 'ilikes', index: 0.2 },
    { domain: 'pn6', index: 0.2 },
    { domain: 'public143177265', index: 0.25 },
    { domain: 'nebula4', index: 0.4 },
    { domain: 'sfdb_ru', index: 0.4 },
    { domain: 'club14347864', index: 0.8 },
    { domain: 'japoznajumir', index: 0.9 },
    { domain: 'guernica', index: 0.9 },
    { domain: 'philosophy_brother', index: 1.0 },
    { domain: 'vk.filosof', index: 0.7 },
    { domain: 'paulo.coelho', index: 0.45 },
    { domain: 'pacanka_status_vk', index: 0.3 },
    { domain: 'club172000', index: 0.7 },
    { domain: 'club16804', index: 0.8 },
    { domain: 'rozhdenie_dnya', index: 0.6 },
    { domain: 'litratre', index: 0.6 },
    { domain: '1poetry', index: 0.45 },
    { domain: 'book', index: 0.5 },
    { domain: 'kinomania', index: 0.35 },
    { domain: 'lhack', index: 0.2 },
    { domain: 'evil_incorparate', index: 0.2 },
    { domain: 'sh_kino', index: 0.8 },
    { domain: 'x.film', index: 0.5 },
])
