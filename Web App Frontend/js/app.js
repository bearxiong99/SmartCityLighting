var app = angular.module('LightsApp', []).controller('MainController', function($scope) {
    $scope.lamps = [
    {
        _id : '5828e870c66c89f5fbdfeeaa',
        title : 'LAMP01',
        description : 'Streetlamp Type C',
        maintainedBy : 'Ankit Sharma',
        address : '2809 Woodway Drive',
        lampStatus : 'Operational',
        lampStatusImage: '../images/blank.png',
        requests: 
        [
            {
                description: 'Bulb outage',
                dateTime: '2016-10-09T02:15:00',
                completed: 'NO',
                status: 'danger'
            },
            {
                description: 'Faulty sensor',
                dateTime: '2016-10-04T17:32:00',
                completed: 'YES',
                status: 'success'
            },
            {
                description: 'Faulty sensor',
                dateTime: '2016-08-15T20:40:00',
                completed: 'YES',
                status: 'success'
            },
            {
                description: 'Faulty sensor',
                dateTime: '2016-06-23T05:18:00',
                completed: 'YES',
                status: 'success'
            },
            {
                description: 'Faulty sensor',
                dateTime: '2016-05-08T12:24:00',
                completed: 'YES',
                status: 'success'
            }
        ],
        weather: 
        {
            temperature : 72,
            humidity : 98,
            windSpeed: 12
        },
        power_usage: 
        {
            today: 2,
            monthly: 60,
            yearly: 530
        },
        proximity : 1,
        collapse_id: 'collapseOne'
    },
    {
        _id : '5828e870c66c89f5fbdfeeab',
        title : 'LAMP02',
        description : 'Streetlamp Type A',
        maintainedBy : 'Chris Chen',
        address : '2210 Pearl Street',
        lampStatus : 'Operational',
        lampStatusImage: '../images/blank.png',
        requests: [],
        weather: 
        {
            temperature : 73,
            humidity : 96,
            windSpeed: 20
        },
        power_usage: 
        {
            today: 1,
            monthly: 52,
            yearly: 440
        },
        proximity : 0,
        collapse_id: 'collapseTwo'
    },
    {
        _id : '5828e870c66c89f5fbdfeeac',
        title : 'LAMP03',
        description : 'Streetlamp Type A',
        maintainedBy : 'Kassidy Knight',
        address : '2222 Pearl Street',
        lampStatus : 'Needs maintenance',
        lampStatusImage: '../images/warning.png',
        requests: 
        [
            {
                description: 'Bulb outage',
                dateTime: '2016-10-09T02:15:00',
                completed: 'NO',
                status: 'danger'
            },
            {
                description: 'Faulty sensor',
                dateTime: '2016-10-04T17:32:00',
                completed: 'YES',
                status: 'success'
            },
            {
                description: 'Faulty sensor',
                dateTime: '2016-08-15T20:40:00',
                completed: 'YES',
                status: 'success'
            }
        ],
        weather: 
        {
            temperature : 74,
            humidity : 92,
            windSpeed: 5
        },
        power_usage: 
        {
            today: 4,
            monthly: 65,
            yearly: 500
        },
        proximity : 0,
        collapse_id: 'collapseThree'
    },
    {
        _id : '5828e870c66c89f5fbdfeead',
        title : 'LAMP04',
        description : 'Streetlamp Type A',
        maintainedBy : 'Pascale Queralt',
        address : '4819 Forest Lane',
        lampStatus : 'Operational',
        lampStatusImage: '../images/blank.png',
                requests: 
        [
            {
                description: 'Bulb outage',
                dateTime: '2016-10-09T02:15:00',
                completed: 'NO',
                status: 'danger'
            },
            {
                description: 'Faulty sensor',
                dateTime: '2016-10-04T17:32:00',
                completed: 'YES',
                status: 'success'
            }
        ],
        weather: 
        {
            temperature : 100,
            humidity : 99,
            windSpeed: 10
        },
        power_usage: 
        {
            today: 3,
            monthly: 70,
            yearly: 520
        },
        proximity : 11,
        collapse_id: 'collapseFour'
    }
    ];

});