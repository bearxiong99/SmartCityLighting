/** Dummy Weather Data **/

var tempWeek = [[0, 70], [1, 65], [2, 68], [3, 69], [4, 72], [5, 80], [7, 81]];
var humidityWeek = [98, 96, 90, 92, 94, 83, 85];
var windWeek = [10, 12, 4, 5, 7, 3, 9];


/** Dummy Power Data **/
var powerWeek = [4, 5, 4, 3, 6, 10, 2];


/** Graphing **/
var w = 140,
    h = 120,
    pad = 20,
    left_pad = 20;
 
var svg = d3.select("#weather-chart")
        .append("svg")
        .attr("width", w)
        .attr("height", h);
 
var x = d3.scale.linear().domain([0, 6]).range([left_pad, w - pad]),
    y = d3.scale.linear().domain([80, 100]).range([pad, h - pad * 2]);
 
var xAxis = d3.svg.axis().scale(x).orient("bottom")
        .ticks(7),
    yAxis = d3.svg.axis().scale(y).orient("left")
        .ticks(20);
 
svg.append("g")
    .attr("class", "axis")
    .attr("transform", "translate(0, " + (h - pad) + ")")
    .call(xAxis);
 
svg.append("g")
    .attr("class", "axis")
    .attr("transform", "translate(" + (left_pad - pad) + ", 0)")
    .call(yAxis);
 
svg.append("text")
    .attr("class", "loading")
    .text("Loading ...")
    .attr("x", function () { return w / 2; })
    .attr("y", function () { return h / 2 - 5; });
 
svg.selectAll(".loading").remove();
 
svg.selectAll("circle")
    .data(tempWeek)
    .enter()
    .append("circle")
    .attr("class", "circle")
    .attr("cx", function (d) { return x(d[1]); })
    .attr("cy", function (d) { return y(d[0]); })
    .transition()
    .duration(800)
    .attr("r", function (d) { return r(d[2]); });
});