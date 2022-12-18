<?php
$HostURL = "https://nthucp.cs.nthu.edu.tw:8890/";

function dumpdata($dir, $save = true)
{
    global $HostURL;
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $HostURL . $dir);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
    $res = curl_exec($ch);
    curl_close($ch);
    //echo $res;
    if (!$res) return false;
    if ($save) file_put_contents($dir, $res);
    return json_decode($res);
}
mkdir("lib");
mkdir("img");
dumpdata("img/close.png");
dumpdata("img/tick_black.png");
dumpdata("Config.js");
dumpdata("DataStore.js");
dumpdata("HistoryStore.js");
dumpdata("Chart.js");
dumpdata("UserDetail.js");
dumpdata("TimeView.js");
dumpdata("TeamSearch.js");
dumpdata("Overview.js");
dumpdata("Scoreboard.js");
dumpdata("Ranking.js");
dumpdata("Ranking.html");
dumpdata("lib/raphael.js");
dumpdata("Ranking.css");


$contests = dumpdata("contests/", false);
//echo var_dump($contests);
if (!is_dir("contests")) mkdir("contests");
file_put_contents("contests/index.json", json_encode($contests));
file_put_contents("contests/.htaccess", "DirectoryIndex index.json");
foreach ($contests as $key => $contest) {
    dumpdata("contests/" . $key);
}

dumpdata("history");
dumpdata("scores");
dumpdata("logo");


$tasks = dumpdata("tasks/", false);
if (!is_dir("tasks")) mkdir("tasks");
file_put_contents("tasks/index.json", json_encode($tasks));
file_put_contents("tasks/.htaccess", "DirectoryIndex index.json");
foreach ($tasks as $key => $task) {
    dumpdata("tasks/" . $key);
}


$teams = dumpdata("teams/", false);
if (!is_dir("teams")) mkdir("teams");
file_put_contents("teams/index.json", json_encode($teams));
file_put_contents("teams/.htaccess", "DirectoryIndex index.json");
foreach ($teams as $key => $team) {
    dumpdata("teams/" . $key);
}

$users = dumpdata("users/", false);
if (!is_dir("users")) mkdir("users");
file_put_contents("users/index.json", json_encode($users));
file_put_contents("users/.htaccess", "DirectoryIndex index.json");
foreach ($users as $key => $user) {
    dumpdata("users/" . $key);
}

//$faces = dumpdata("faces",false);
if (!is_dir("faces")) mkdir("faces");
foreach ($users as $key => $user) {
    dumpdata("faces/" . $key);
}


//$flags = dumpdata("flags",false);
if (!is_dir("flags")) mkdir("flags");
foreach ($teams as $key => $team) {
    dumpdata("flags/" . $key);
}


if (!is_dir("sublist")) mkdir("sublist");
foreach ($users as $key => $user) {
    dumpdata("sublist/" . $key);
}
