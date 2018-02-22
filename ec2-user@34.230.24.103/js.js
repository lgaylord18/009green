const team = [
    {
        name: 'Andres Galindo',
        role: 'Engineer',
    },
    {
        name: 'Anika Yasmin',
        role: 'Engineer',
    },
    {
        name: 'Donovan Sienkiewicz',
        role: 'Engineer',
    },
    {
        name: 'Emily Damato',
        role: 'Engineer',
    },
    {
        name: 'Eric Ponce',
        role: 'Engineer',
    },
    {
        name: 'Greg Cartagena',
        role: 'Engineer',
    },
    {
        name: 'Ishan Meswani',
        role: 'Engineer',
    },
    {
        name: 'JD Heyns',
        role: 'Engineer',
    },
    {
        name: 'Jana Saadi',
        role: 'Engineer',
    },
    {
        name: 'Jeremy Bogle',
        role: 'Engineer',
    },
    {
        name: 'Josh Woodard',
        role: 'Engineer',
    },
    {
        name: 'Katherine Paseman',
        role: 'Engineer',
    },
    {
        name: 'Liza Gaylord',
        role: 'Engineer',
    },
    {
        name: 'Lucia Liu',
        role: 'Engineer',
    },
    {
        name: 'Mary Thielking',
        role: 'Engineer',
    },
    {
        name: 'Pelkins Ajanoh',
        role: 'Engineer',
    },
    {
        name: 'Yasmin Chavez',
        role: 'Engineer',
    },
]

$(document).ready(function() {
    let i = 0;
    let col = 1;
    team.forEach(member => {
        if (i > 5) {
            i = 0;
            col += 1;
        }
        i += 1;
        $(`#col${col}`).append(`<div class="member">${member.name}</div>`);
    })

    $('#learn-more-btn').click(() => {
        $('#instructions').addClass('shown');
        $('#dimmer').addClass('on');
    })
    $('#team-btn').click(() => {
        $('#team').addClass('shown');
        $('#dimmer').addClass('on');
    })
    $('#dimmer').click(() => {
        $('#instructions').removeClass('shown');
        $('#team').removeClass('shown');
        $('#dimmer').removeClass('on');
    })
});
