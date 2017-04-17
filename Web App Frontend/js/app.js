var app = angular.module('LightsApp', []);

app.controller('MainController', ['$scope', '$interval', '$http', function ($scope, $interval, $http) {
    
    var auth = btoa("admin:superuser");
    headers = {"Authorization": "Basic" + auth};
    
    $scope.lamps = new Object();
    $scope.keys = [];
    $scope.chartType = 'Temperature';
    $scope.tabSwitch = true;
    
    $scope.dummy = [
        {
            lamp_id : 1,
            owner : 'admin',
            address : '2809 Woodway Dr.',
            latitude: 30.365246,
            longitude: -97.766667,
            operational : true,
            operations: [
                {
                    operational: true,
                    dateTime: '2016-10-09T02:15:00',
                    status: 'success'
                },
                {
                    operational: false,
                    dateTime: '2016-10-04T17:32:00',
                    status: 'danger'
                },
                {
                    operational: true,
                    dateTime: '2016-08-15T20:40:00',
                    status: 'success'
                },
                {
                    operational: true,
                    dateTime: '2016-06-23T05:18:00',
                    status: 'success'
                },
                {
                    operational: true,
                    dateTime: '2016-05-08T12:24:00',
                    status: 'success'
                }
            ],
            weather:
                {
                    temperature : 72,
                    humidity : 98
                },
            light: "382.080",
            motion_count: 659,
            motion_detected: true,
            collapse_id: 'collapseOne'
        },
        {
            lamp_id : 2,
            owner : 'admin',
            address : '2210 Pearl St.',
            latitude: 30.286408,
            longitude: -97.746623,
            operational : true,
            operations: [],
            weather:
                {
                    temperature : 73,
                    humidity : 96
                },
            light: "382.080",
            motion_count: 659,
            motion_detected: true,
            collapse_id: 'collapseTwo'
        },
        {
            lamp_id : 3,
            owner : 'admin',
            address : '2222 Pearl St.',
            latitude: 30.287029,
            longitude: -97.746717,
            operational: true,
            operations: [
                {
                    operational: false,
                    dateTime: '2016-10-09T02:15:00',
                    status: 'danger'
                },
                {
                    operational: true,
                    dateTime: '2016-10-04T17:32:00',
                    status: 'success'
                },
                {
                    operational: true,
                    dateTime: '2016-08-15T20:40:00',
                    status: 'success'
                }
            ],
            weather:
                {
                    temperature : 74,
                    humidity : 92
                },
            light: "382.080",
            motion_count: 659,
            motion_detected: true,
            collapse_id: 'collapseThree'
        }
    ];

    /*************** PULL LAMP DATA FROM DATABASE ******************/
    $http.get('http://ec2-54-149-179-136.us-west-2.compute.amazonaws.com:8000/smartcityapi/?format=json', {headers: headers}).
        then(function (response) {
            var count = 20; // twenty records per page
            var lampData = response.data.results;

            $scope.lamps[lampData[0].lamp_id] = [
                {
                    'date_time': new Date(lampData[0].date_time),
                    'lamp_id': lampData[0].lamp_id,
                    'temperature': parseFloat(lampData[0].temperature).toFixed(2),
                    'humidity': parseFloat(lampData[0].humidity).toFixed(2),
                    'light': parseFloat(lampData[0].light).toFixed(2),
                    'motion_count': lampData[0].motion_count,
                    'motion_detected': lampData[0].motion_detected,
                    'operational': lampData[0].operational,
                    'owner': lampData[0].owner,
                    'count': 1,
                    'address': lampData[0].address
                }
            ];

            var k;
            for (k = 1; k < count; k += 1) {
                if (lampData[k].lamp_id in $scope.lamps) {
                    $scope.lamps[lampData[k].lamp_id].push(
                        {
                            'date_time': new Date(lampData[k].date_time),
                            'lamp_id': lampData[k].lamp_id,
                            'temperature': parseFloat(lampData[k].temperature).toFixed(2),
                            'humidity': parseFloat(lampData[k].humidity).toFixed(2),
                            'light': parseFloat(lampData[k].light).toFixed(2),
                            'motion_count': lampData[k].motion_count,
                            'motion_detected': lampData[k].motion_detected,
                            'operational': lampData[k].operational,
                            'owner': lampData[k].owner,
                            'count': $scope.lamps[lampData[k].lamp_id].length + 1,
                            'address': lampData[k].address
                        }
                    );
                } else {
                    $scope.lamps[lampData[k].lamp_id] = [
                        {
                            'date_time': new Date(lampData[k].date_time),
                            'lamp_id': lampData[k].lamp_id,
                            'temperature': parseFloat(lampData[k].temperature).toFixed(2),
                            'humidity': parseFloat(lampData[k].humidity).toFixed(2),
                            'light': parseFloat(lampData[k].light).toFixed(2),
                            'motion_count': lampData[k].motion_count,
                            'motion_detected': lampData[k].motion_detected,
                            'operational': lampData[k].operational,
                            'owner': lampData[k].owner,
                            'count': 1,
                            'address': lampData[k].address
                        }
                    ];
                }
            }
            $scope.keys = Object.keys($scope.lamps);
        });
}]);
              
/****************************** WEATHER CHART SCRIPT ********************************/
app.directive('linearChart', function ($parse, $window) {
    return {
        restrict: 'EA',
        template: "<svg width='550' height='200'></svg>",
        link: function (scope, elem, attrs) {
            var exp = $parse(attrs.chartData);

            var DataToPlot = exp(scope);
            DataToPlot = DataToPlot.slice().reverse();
            var padding = 10;
            var pathClass = "path";
            var xScale, yScale, xAxisGen, yAxisGen, lineFun;

            var d3 = $window.d3;
            var rawSvg = elem.find('svg');
            var svg = d3.select(rawSvg[0]);

            scope.$watch('tabSwitch', function () {
                exp = $parse(attrs.chartData);
                DataToPlot = exp(scope);
                DataToPlot = DataToPlot.slice().reverse();
                redrawLineChart();
            });

            scope.$watch('chartType', function () {
                exp = $parse(attrs.chartData);
                DataToPlot = exp(scope);
                DataToPlot = DataToPlot.slice().reverse();
                redrawLineChart();
            });

            function setChartParameters() {
                var myDomain = DataToPlot.map(function (a) {return a.count; });
                var myData;

                switch (scope['chartType']) {
                case 'Temperature':
                    myData = DataToPlot.map(function (a) {return a.temperature; });
                    break;
                    
                case 'Humidity':
                    myData = DataToPlot.map(function (a) {return a.humidity; });
                    break;
                    
                case 'Motion Count':
                    myData = DataToPlot.map(function (a) {return a.motion_count; });
                    break;
                    
                default:
                    myData = DataToPlot.map(function (a) {return a.temperature; });
                    break;
                }


                xScale = d3.scale.linear()
                    .domain([myDomain[0], myDomain[myDomain.length - 1]])
                    .range([padding + 5, rawSvg.attr("width") - padding]);

                yScale = d3.scale.linear()
                    .domain([d3.min(myData, function (d) { return parseInt(d); }), d3.max(myData, function (d) { return parseInt(d); })])
                    .range([rawSvg.attr("height") - padding, 0]);

                xAxisGen = d3.svg.axis()
                    .scale(xScale)
                    .orient("bottom")
                    .ticks(10);

                yAxisGen = d3.svg.axis()
                    .scale(yScale)
                    .orient("left")
                    .ticks(5);

                switch (scope['chartType']) {
                case 'Temperature':
                    lineFun = d3.svg.line()
                        .x(function (d) {return xScale(d.count); })
                        .y(function (d) {return yScale(d.temperature); })
                        .interpolate("basis");
                    break;
                case 'Humidity':
                    lineFun = d3.svg.line()
                        .x(function (d) {return xScale(d.count); })
                        .y(function (d) {return yScale(d.humidity); })
                        .interpolate("basis");
                    break;
                case 'Motion Count':
                    lineFun = d3.svg.line()
                        .x(function (d) {return xScale(d.count); })
                        .y(function (d) {return yScale(d.motion_count); })
                        .interpolate("basis");
                    break;
                default:
                    lineFun = d3.svg.line()
                        .x(function (d) {return xScale(d.count); })
                        .y(function (d) {return yScale(d.temperature); })
                        .interpolate("basis");
                    break;
                }
            }

            function drawLineChart() {

                setChartParameters();

                svg.append("svg:g")
                    .attr("class", "x axis")
                    .attr("transform", "translate(0,180)")
                    .call(xAxisGen);

                svg.append("svg:g")
                    .attr("class", "y axis")
                    .attr("transform", "translate(20,0)")
                    .call(yAxisGen);

                svg.append("svg:path")
                    .attr({
                        d: lineFun(DataToPlot),
                        "stroke": "blue",
                        "stroke-width": 2,
                        "fill": "none",
                        "class": pathClass
                    });
            }

            function redrawLineChart() {

                setChartParameters();

                svg.selectAll("g.y.axis").call(yAxisGen);

                svg.selectAll("g.x.axis").call(xAxisGen);

                svg.selectAll("." + pathClass)
                    .attr({
                        d: lineFun(DataToPlot)
                    });
            }

            drawLineChart();
        }
    };
});

/* FILTER FOR SEARCH FUNCTION */
app.filter('myFilter', function () {
    return function (items, search) {
        var result = [];
        var i;
        angular.forEach(items, function (value, key) {
            for (i = 0; i < value.length; i = i + 1) {
                angular.forEach(value[i], function (value2, key2) {
                    if (value2 === search) {
                        result.push(key);
                    }
                });
            }
        });
        return result;
    };
});

app.filter('reverse', function () {
    return function(items) {
        return items.slice().reverse();
    };
});                                 


/************************** GOOGLE MAPS SCRIPT ***************************/
var map;

function initMap() {
    lamp1 = {lat: 30.365246, lng: -97.766667};
    lamp2 = {lat: 30.286408, lng: -97.746623};
    lamp3 = {lat: 30.287029, lng: -97.746717};
    map = new google.maps.Map(document.getElementById('map'), {
        zoom: 12,
        center: {lat: 30.32, lng: -97.72}
    });
    var marker = new google.maps.Marker({
        position: lamp1,
        map: map
    });
    var marker = new google.maps.Marker({
        position: lamp2,
        map: map
    });
    var marker = new google.maps.Marker({
        position: lamp3,
        map: map
    });
}


/* Selecting Map View list items */
$(function () {
    console.log('ready');
    
    $('.list-group-item').click(function (e) {
        e.preventDefault();
        
        $that = $(this);
        
        $previous = $that.hasClass('list-active');
        
        $that.parent().find('.list-group-item').removeClass('list-active');
        if (!($previous)) {
            $that.addClass('list-active');
        }
    });
});