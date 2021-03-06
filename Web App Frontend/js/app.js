var app = angular.module('LightsApp', []);

app.controller('MainController', ['$scope', '$interval', '$http', function ($scope, $interval, $http) {
    
    var auth = btoa("admin:superuser");
    headers = {"Authorization": "Basic" + auth};
    
    $scope.lamps = new Object();
    $scope.keys = [];
    $scope.chartType = 'Temperature';
    $scope.tabSwitch = true;
    $scope.selected = 0;
    
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
                    'address': lampData[0].address,
                    'latitude': parseFloat(lampData[0].latitude).toFixed(6),
                    'longitude': parseFloat(lampData[0].longitude).toFixed(6)
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
                            'address': lampData[k].address,
                            'latitude': parseFloat(lampData[k].latitude).toFixed(6),
                            'longitude': parseFloat(lampData[k].longitude).toFixed(6)
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
                            'address': lampData[k].address,
                            'latitude': parseFloat(lampData[k].latitude).toFixed(6),
                            'longitude': parseFloat(lampData[k].longitude).toFixed(6)
                        }
                    ];
                }
            }
            $scope.keys = Object.keys($scope.lamps);
        });
    
    var mapOptions = {
        zoom: 4,
        center: new google.maps.LatLng(40, -98)
    }
    
    $scope.map = new google.maps.Map(document.getElementById('map'), mapOptions);
    
    $scope.markers = [];
    
    var infoWindow = new google.maps.InfoWindow();
    
    var createMarker = function (info) {
        
        var marker = new google.maps.Marker({
            map: $scope.map,
            position: new google.maps.LatLng(info.latitude, info.longitude),
            title: info.lamp_id
        });
        marker.content = '<div class="infoWindowContent>' + info.address + '</div>';
        
        google.maps.event.addListener(marker, 'click', function () {
            infoWindow.setContent('<h2>' + marker.title + '</h2>' + marker.content);
            infoWindow.open($scope.map, marker);
        });
        
        $scope.markers.push(marker);
    };
        
    for (i = 0; i < $scope.dummy.length; i++) {
            createMarker($scope.dummy[i]);
    }
        
    $scope.openInfoWindow = function (e, selectedMarker) {
            e.preventDefault();
            google.maps.event.trigger(selectedMarker, 'click');
    };
    
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


/************************** GOOGLE MAPS SCRIPT ***************************/
/*function initMap() {
    var lamp1 = {lat: 30.2911160, lng: -97.746465};
    var lamp2 = {lat: 30.286408, lng: -97.746623};
    var lamp3 = {lat: 30.287029, lng: -97.746717};
    var lamp4 = {lat: 30.20, lng: -97.70};
    var markers = [];
    
    map = new google.maps.Map(document.getElementById('map'), {
    });
    
    var marker1 = new google.maps.Marker({
        position: lamp1,
        map: map
    });
    var marker2 = new google.maps.Marker({
        position: lamp2,
        map: map
    });
    var marker3 = new google.maps.Marker({
        position: lamp3,
        map: map
    });
    
    markers = [marker1, marker2, marker3];
    var bounds = new google.maps.LatLngBounds();
    for(var i=0; i<markers.length; i++){
        bounds.extend(markers[i].getPosition());
    };
    
    map.setCenter(bounds.getCenter());
    map.fitBounds(bounds);
};*/