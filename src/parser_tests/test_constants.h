#include <string>

namespace test_constants {
    std::string html = R"(
    <!DOCTYPE html>
    <html><head><meta name="hmac-token-name" content="Ajax-Token">

        <meta charset="utf-8">

        <meta name="viewport" content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">

        <title>Табель успеваемости</title>
        <meta name="keywords" content="elschool, электронная школа, электронный журнал, электронный дневник">
        <meta name="description" content="ELSCHOOL - проект электронной школы, предоставляющий большие возможности по ведению учебного процесса для учителей, учеников и их родителей.">

        <link rel="shortcut icon" href="/Content/images/page-icon-2.ico" type="image/x-icon">

        <link href="/Content/css/bootstrap?v=yrm-2_oE9TUxvwGXbC96vVjD6Yv6PQ6V__2dpb2BBXg1" rel="stylesheet">

        <link href="/Content/css/style?v=e-FAu1ocdX7puvH5wZDv-ea-YhApObtEwCu7xOLBXcA1" rel="stylesheet">

        <link href="/Content/css/menu?v=Cd-IGAxSw7AmhjLJT1BNlSl44XmhiiAk6t2FE3hGXFk1" rel="stylesheet">


        <script async="" src="https://mc.yandex.ru/metrika/tag.js"></script><script charset="utf-8" src="/11111111111111111aaaa111.js?1696412155655"></script>
        <script src="/Script/plugins?v=wfgO0xNOh0FlYbXkdHYRv07zqw4UZ8Y1_8l5zn4zLg81"></script>

        <script src="/Script/main?v=2ZrMEdHQ2euZSh-27qqYuYI_UDpeaEZ7OsbYpimbckY1"></script>

        <script src="/Script/menu?v=uRFEQ_xq582VsiayZPD-RuvpCv8ypHrFbgUHBDGz1hU1" defer=""></script>



    </head>
    <body><noscript><img src="/11b162ab51620eeaa9acfcab7ad4b479.gif" width="0" height="0" alt="" /></noscript>



    <header>

        <div class="navbar-cheat"></div>
        <nav class="fixed-top justify-content-start">

            <div class="new-menu" style="left: -26em;">
                <div class="nav-shadow"></div>
                <div class="menu-wrapper"><div class="menu-container" style="display: none;"><ul class="menu-header" style=""><li><a class="back"><span>Главное меню</span></a></li><hr style="color: #184656; background-color: #184656; margin: 10px 20px 0;"></ul><div><ul class="menu-body"><li><a class="title" href="/users/privateoffice/edit"><span>Настройки</span></a></li></ul></div></div><div class="menu-container" style="display: none;"><ul class="menu-header" style=""><li><a class="back"><span>Главное меню</span></a></li><hr style="color: #184656; background-color: #184656; margin: 10px 20px 0;"></ul><div><ul class="menu-body"><li><a class="title" href="/districts/00/schools/000/classes/000000"><span>3А</span></a></li></ul></div></div><div class="menu-container"><ul class="menu-header" style="display: none;"></ul><div style="height: 752px;"><ul class="menu-body"><li><a class="title" href="/users/privateoffice" data-type="Account"><span>Личный кабинет</span></a><a class="next"><span></span></a></li><li><a class="title" href="/districts/00/schools/000" data-type="Institute"><span>ФГБУ АОУ "Уездная гимназия имени академика Чебурашкина"</span></a></li><li><a class="next" data-type="DepartmentList"><span>Классы</span></a></li><li><a class="title" href="/kconferences/index" data-type="Messages"><span>Сообщения</span></a></li><li><a class="title" href="/users/diaries" data-type="DiaryList"><span>Дневник</span></a></li><li><a class="next" data-type="Settings"><span>Настройки меню</span></a></li><li><a class="exit" href="Exit" data-type="Exit"><span>Выйти из системы</span></a></li></ul></div></div><div class="menu-container" style="display: none;"><ul class="menu-header" style=""><li><a class="back"><span>Главное меню</span></a></li><hr style="color: #184656; background-color: #184656; margin: 10px 20px 0;"></ul><div><ul class="menu-body"><li><a class="title" href="Update"><span>Обновить меню</span></a></li></ul></div></div></div>
            </div>

            <div class="nav-container" style="display: flex;">
                <a class="MenuButton header-link">
                    <div class="d-flex">
                        <div id="nav-icon3">
                            <span></span>
                            <span></span>
                            <span></span>
                            <span></span>
                        </div>
                        <div class="mx-2 d-none d-md-block" id="menuTitle" unselectable="on">
                            <div id="menuTitle1">Меню</div>
                            <div id="menuTitle2">Закрыть</div>
                        </div>
                    </div>
                </a>

                <a class="today-journal-button header-link"><span class="d-none d-md-block">Расписание</span></a>

                <a class="d-none d-md-flex header-link" id="UserFIO" href="/users/privateoffice">Иван Рюрикович</a>

            </div>

            <div class="today-journal">



            </div>
        </nav>

        <input type="hidden" id="model_menu_user_id" value="0000000">
        <input type="hidden" id="model_menu_is_teacher" value="False">
        <input type="hidden" id="model_menu_user_role" value="8">




    </header>

    <main class="container-fluid">
        ﻿

        <script>
            if (localStorage.getItem('diary_dark_theme_0000000') == 'true') {
                switch_theme('dark');
            }

            function switch_theme(theme) {
                var d = document.documentElement.style;
                d.setProperty('--back', 'var(--' + theme + '-back)');
                d.setProperty('--back-second', 'var(--' + theme + '-back-second)');
                d.setProperty('--border-bold', 'var(--' + theme + '-border-bold)');
                d.setProperty('--border', 'var(--' + theme + '-border)');
                d.setProperty('--header', 'var(--' + theme + '-header)');
                d.setProperty('--font', 'var(--' + theme + '-font)');
                d.setProperty('--font-header', 'var(--' + theme + '-font-header)');
                d.setProperty('--font-second', 'var(--' + theme + '-font-second)');
                d.setProperty('--icon', 'var(--' + theme + '-icon)');
                d.setProperty('--link', 'var(--' + theme + '-link)');
                d.setProperty('--late', 'var(--' + theme + '-late)');
                d.setProperty('--placeholder', 'var(--' + theme + '-placeholder)');
                d.setProperty('--popover', 'var(--' + theme + '-popover)');
                d.setProperty('--highlight', 'var(--' + theme + '-highlight)');
                d.setProperty('--mark1', 'var(--' + theme + '-mark1)');
                d.setProperty('--mark2', 'var(--' + theme + '-mark2)');
                d.setProperty('--mark3', 'var(--' + theme + '-mark3)');
                d.setProperty('--mark4', 'var(--' + theme + '-mark4)');
                d.setProperty('--mark5', 'var(--' + theme + '-mark5)');
            }
        </script>
        <style>

            :root {
                /* Светлая тема */
                --default-back: #FFF;
                --default-back-second: #FAFAFA;
                --default-border: #dee2e6;
                --default-border-bold: #d0cfcf;
                --default-header: #E9F0F5;
                --default-font: #1a1a1a;
                --default-font-header: #7F7F7F;
                --default-font-second: #777;
                --default-icon: #A7A7A7;
                --default-link: #0687b1;
                --default-late: #E28007;
                --default-placeholder: #dee2e6;
                --default-popover: #FFF;
                --default-highlight: rgba(25, 118, 210, 0.08);
                --default-mark1: #ffb6c1;
                --default-mark2: #ffb6c1;
                --default-mark3: #f0e68c;
                --default-mark4: #87ceeb;
                --default-mark5: #98fb98;
                --default-markH: #d3d3d3;
                /* Тёмная тема */
                --dark-back: #495960;
                --dark-back-second: #293F4D;
                --dark-border: #1A1A1A;
                --dark-border-bold: #000000;
                --dark-header: #4a5f68;
                --dark-font: #ddd;
                --dark-font-header: #fff;
                --dark-font-second: #afafaf;
                --dark-icon: #A7A7A7;
                --dark-link: #00d4ff;
                --dark-late: #E28007;
                --dark-placeholder: #afafaf;
                --dark-popover: #4a5f68;
                --dark-highlight: rgba(255, 255, 255, 0.15);
                --dark-mark1: #d46e7d;
                --dark-mark2: #d46e7d;
                --dark-mark3: #afa760;
                --dark-mark4: #6195ab;
                --dark-mark5: #6fb56f;
                --dark-markH: #909090;
                /*  Дефолтно выбрана белая  */
                --back: var(--default-back);
                --back-second: var(--default-back-second);
                --border: var(--default-border);
                --border-bold: var(--default-border-bold);
                --header: var(--default-header);
                --font: var(--default-font);
                --font-header: var(--default-font-header);
                --font-second: var(--default-font-second);
                --icon: var(--default-icon);
                --link: var(--default-link);
                --late: var(--default-late);
                --placeholder: var(--default-placeholder);
                --popover: var(--default-popover);
                --highlight: var(--default-highlight);
                --mark1: var(--default-mark1);
                --mark2: var(--default-mark2);
                --mark3: var(--default-mark3);
                --mark4: var(--default-mark4);
                --mark5: var(--default-mark5);
            }

            body {
                padding: 0 !important;
                background-color: var(--back-second);
                color: var(--font);
            }

            select, input, textarea {
                background-color: var(--back) !important;
                color: var(--font-header) !important;
            }

            div.new-menu li > input[type="search"] {
                background-color: #184656 !important;
                color: #fff !important;
            }

            .dropdown-menu {
                background-color: var(--back) !important;
                box-shadow: 0px 5px 5px -3px rgba(0, 0, 0, 0.2), 0px 8px 10px 1px rgba(0, 0, 0, 0.14), 0px 3px 14px 2px rgba(0, 0, 0, 0.12);
                color: var(--font) !important;
            }

            .today-journal {
                background-color: var(--back);
            }

            .today-journal a[href] {
                color: var(--link);
            }

            .modal-content {
                background-color: var(--back);
            }

            .modal-header .close, .today-journal .close {
                padding: 0;
                margin: -0.2rem 0rem 0rem auto;
                text-shadow: none;
                color: var(--font-second);
            }

            .modal-header .close:not(:disabled):not(.disabled):focus, .modal-header .close:not(:disabled):not(.disabled):hover, .today-journal .close:not(:disabled):not(.disabled):focus, .today-journal .close:not(:disabled):not(.disabled):hover {
                color: var(--font);
                outline: none;
            }

            .popover {
                background-color: var(--popover);
                z-index: 10;
            }

            .popover * {
                color: var(--font);
            }

            .popover[x-placement="top"] .arrow:after {
                border-top-color: var(--popover);
            }

            .popover[x-placement="right"] .arrow:after {
                border-right-color: var(--popover);
            }

            .popover[x-placement="bottom"] .arrow:after {
                border-bottom-color: var(--popover);
            }

            .popover[x-placement="left"] .arrow:after {
                border-left-color: var(--popover);
            }

            .document-container__footer {
                background-color: var(--back-second);
            }

            .document-container__footer .container-fluid {
                background-color: var(--header) !important;
            }

            .document-container__footer li {
                color: var(--font-second);
            }

            .document-container__footer a[href] {
                color: var(--link);
            }

            .DivForGradesTable {
                overflow-x: auto;
            }

            .DivForGradesTable .GradesTable {
                margin-top: 30px;
                background-color: var(--back);
            }

            .DivForGradesTable .GradesTable td {
                height: 46px;
                border-color: var(--border);
            }

            .DivForGradesTable .GradesTable thead tr {
                background-color: var(--header);
            }

            .DivForGradesTable .GradesTable thead tr th {
                color: var(--font-header);
                border-color: var(--border-bold);
            }

            .DivForGradesTable .GradesTable thead tr th.grades-average-th {
                max-width: 60px;
            }

            .DivForGradesTable .GradesTable.MobileGrades thead tr th {
                border-bottom: 1px solid var(--border);
                border-top: 2px solid var(--border);
            }

            .DivForGradesTable .GradesTable.MobileGrades .grades-period-name {
                background-color: var(--header);
                color: var(--font-header);
                text-transform: uppercase;
                white-space: nowrap;
                font-weight: 500;
            }

            .DivForGradesTable .GradesTable .grades-lesson-number {
                color: var(--font-second);
                border-right: none;
                max-width: 24px;
            }

            .DivForGradesTable .GradesTable .grades-lesson {
                border-left: none;
            }

            .DivForGradesTable .GradesTable .grades-average {
                background-color: var(--back);
            }

            .DivForGradesTable .GradesTable .grades-average.mark1 {
                background-color: var(--mark1);
            }

            .DivForGradesTable .GradesTable .grades-average.mark2 {
                background-color: var(--mark2);
            }

            .DivForGradesTable .GradesTable .grades-average.mark3 {
                background-color: var(--mark3);
            }

            .DivForGradesTable .GradesTable .grades-average.mark4 {
                background-color: var(--mark4);
            }

            .DivForGradesTable .GradesTable .grades-average.mark5 {
                background-color: var(--mark5);
            }

            @media(max-width:1000px) {
                .DivForGradesTable .GradesTable:not(.MobileGrades) {
                    display: none;
                }

                .DivForGradesTable .GradesTable.MobileGrades {
                    display: table;
                }

                .GradesNavigation .switch-desktop-mobile {
                    display: block;
                }
            }

            @media(min-width:1000px) {
                .DivForGradesTable .GradesTable:not(.MobileGrades) {
                    display: table;
                }

                .DivForGradesTable .GradesTable.MobileGrades {
                    display: none;
                }

                .GradesNavigation .switch-desktop-mobile {
                    display: none;
                }
            }

            .navigation {
                position: sticky;
                top: 44px;
                background-color: var(--back);
                z-index: 12;
                margin: 0 0 15px;
                height: 60px;
                padding: 12px 30px;
                border: 1px solid var(--border);
                border-radius: 3px;
            }

            .navigation__fio {
                font-size: 18px;
                line-height: 34px;
                padding: 0 0 0 10px;
                text-align: center;
                justify-content: center;
            }

            .navigation__fio > a {
                color: var(--link);
                text-decoration: none;
                padding: 0 5px;
                border-radius: 3px;
                white-space: nowrap;
                overflow: hidden;
                text-overflow: ellipsis;
                margin: 0 auto;
                text-align: center;
            }

            .navigation__fio > a:hover {
                background-color: var(--highlight);
            }

            .navigation__years > .btn {
                border-color: transparent !important;
                background-color: transparent !important;
                color: var(--link) !important;
                padding: 0 5px;
                width: 50px;
                height: 34px;
                box-shadow: none !important;
                margin-top: -5px;
                margin-left: 15px;
            }

            .navigation__years > .btn:hover, .navigation__years > .btn:focus, .navigation__years > .btn:active {
                background-color: var(--highlight) !important;
                border-color: transparent !important;
                color: var(--link) !important;
            }

            .navigation__years > .btn:after {
                display: none;
            }

            .navigation__years .dropdown-menu {
                min-width: 50px;
            }

            .navigation__years .dropdown-item:hover {
                background-color: var(--header);
                cursor: pointer;
            }

            .navigation__years .dropdown-item:active {
                background-color: var(--link);
                color: white !important;
            }

            .navigation__type > .btn {
                padding: 4px 6px;
                color: var(--link) !important;
                border: none;
                background-color: transparent;
                box-shadow: none;
            }

            .navigation__type > .btn:hover {
                background-color: var(--highlight);
            }

            .diary__theme, .download-to-excel {
                border: none;
                border-radius: 50%;
                width: 34px;
                height: 34px;
                padding: 0 !important;
                box-shadow: none !important;
                font-size: 22px;
                color: var(--link) !important;
                background-color: transparent;
            }

            .diary__theme > .fa {
                line-height: 32px;
                padding: 1px;
            }

            .download-to-excel > .fa {
                line-height: 32px;
                padding: 2px 1px 1px 1px;
            }

            .download-to-excel {
                font-size: 19px;
            }

            @media (max-width: 991px) {
                .navigation > * {
                    margin: 0 auto;
                }

                .navigation .popover {
                    display: none;
                }

                .navigation__fio {
                    padding: 0;
                }
            }

            .navigation_mobile {
                border: 1px solid var(--border);
                background-color: var(--back);
                border-radius: 3px;
                padding: 5px;
            }

            .navigation_mobile > .btn {
                color: var(--link);
                width: 100%;
                text-align: left;
                box-shadow: none;
                background-color: transparent;
            }

            .navigation_mobile > .btn:focus {
                background-color: var(--highlight);
            }
        </style>
        <div class="navigation d-flex">
            <div class="d-flex col-3 col-lg-4 navigation__fio">
                <div class="navigation__years dropright">
                    <button class="btn btn-secondary dropdown-toggle" type="button" id="dropdownMenuButton" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                    <span class="navigation__years__department">
                            2А
                        </span> <i class="fa fa-angle-down"></i>
                    </button>
                    <div class="dropdown-menu" aria-labelledby="dropdownMenuButton">
                        <a class="dropdown-item " model-start-year="2021" model-end-year="2022" model-institute-id="000" model-department-id="000000">
                            1А
                        </a>
                        <a class="dropdown-item navigation__years_selected" model-start-year="2022" model-end-year="2023" model-institute-id="000" model-department-id="000000">
                            2А
                        </a>
                        <a class="dropdown-item " model-start-year="2023" model-end-year="2024" model-institute-id="000" model-department-id="000000">
                            3А
                        </a>
                    </div>
                </div>
                <a href="/users/0000000" data-popover-content="Рюрикович Иван Васильевич" class="d-none d-lg-block" data-original-title="" title="">Рюрикович Иван Васильевич</a>
            </div>
            <div class="col-lg-6 d-none d-lg-block navigation__type p-0 text-center">
                <a href="details?rooId=00&amp;instituteId=000&amp;departmentId=000000&amp;pupilId=0000000" class="btn">Дневник</a>
                <a href="gradesandabsences?rooId=00&amp;instituteId=000&amp;departmentId=000000&amp;pupilId=0000000" class="btn">Табель с учётом посещаемости</a>
                <a href="results?rooId=00&amp;instituteId=000&amp;departmentId=000000&amp;pupilId=0000000" class="btn">Итоговые</a>
            </div>
            <div class="col-lg-2 text-right">
                <button type="button" class="btn diary__theme" data-popover-content="Переключить светлую/тёмную тему" data-original-title="" title=""><i class="fa fa-moon-o"></i></button>
                <button type="button" data-popover-content="Выгрузить в Excel" class="btn download-to-excel" data-table-name="grades-table" data-file-name="Табель успеваемости.xls" data-original-title="" title="">
                    <i class="fa fa-file-excel-o"></i>
                </button>
            </div>
        </div>
        <div class="d-block d-lg-none navigation_mobile">
            <a href="details?rooId=00&amp;instituteId=000&amp;departmentId=000000&amp;pupilId=0000000" class="btn">Дневник</a>
            <a href="gradesandabsences?rooId=00&amp;instituteId=000&amp;departmentId=000000&amp;pupilId=0000000" class="btn">Табель с учётом посещаемости</a>
            <a href="results?rooId=00&amp;instituteId=000&amp;departmentId=000000&amp;pupilId=0000000" class="btn">Итоговые</a>
        </div>
        <div class="DivForGradesTable">
            <h4 class="text-center mt-3 mt-lg-2">Рюрикович Иван Васильевич</h4>
            <table class="table table-bordered GradesTable" id="grades-table">
                <thead>
                <tr>
                    <th colspan="2">Предмет</th>
                    <th class="grades-average-th">Сред балл</th>
                    <th>1 четверть</th>
                    <th class="grades-average-th">Сред балл</th>
                    <th>2 четверть</th>
                    <th class="grades-average-th">Сред балл</th>
                    <th>3 четверть</th>
                    <th class="grades-average-th">Сред балл</th>
                    <th>4 четверть</th>
                </tr>
                </thead>
                <tbody>

                <tr lesson="1">
                    <td class="grades-lesson-number">1</td>
                    <td class="grades-lesson">Эльфийский язык как государственный язык Лесного Королевства</td>
                    <td class="grades-average mark2">2</td>
                    <td class="grades-marks">
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 28.09.2022<p>Дата проставления: 28.10.2022" data-original-title="" title="">2</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 19.10.2022<p>Дата проставления: 28.10.2022" data-original-title="" title="">2</span>

                    </td>
                    <td class="grades-average mark3">3</td>
                    <td class="grades-marks">
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 16.11.2022<p>Дата проставления: 25.11.2022" data-original-title="" title="">3</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 23.11.2022<p>Дата проставления: 25.11.2022" data-original-title="" title="">3</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 14.12.2022<p>Дата проставления: 31.10.2022" data-original-title="" title="">3</span>

                    </td>
                    <td class="grades-average mark4">4</td>
                    <td class="grades-marks">
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 08.02.2023<p>Дата проставления: 26.04.2023" data-original-title="" title="">4</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 15.02.2023<p>Дата проставления: 26.04.2023" data-original-title="" title="">4</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 01.03.2023<p>Дата проставления: 26.04.2023" data-original-title="" title="">4</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 15.03.2023<p>Дата проставления: 26.04.2023" data-original-title="" title="">4</span>

                    </td>
                    <td class="grades-average mark5">5</td>
                    <td class="grades-marks">
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 05.04.2023<p>Дата проставления: 26.04.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 19.04.2023<p>Дата проставления: 26.04.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 26.04.2023<p>Дата проставления: 26.04.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 03.05.2023<p>Дата проставления: 26.05.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 10.05.2023<p>Дата проставления: 26.05.2023" data-original-title="" title="">5</span>

                    </td>
                </tr>



                <tr lesson="2">
                    <td class="grades-lesson-number">2</td>
                    <td class="grades-lesson">Алхимия</td>
                    <td class="grades-average mark3">3,33</td>
                    <td class="grades-marks">
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 13.09.2022<p>Дата проставления: 15.10.2022" data-original-title="" title="">3</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 20.09.2022<p>Дата проставления: 15.10.2022" data-original-title="" title="">3</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 27.09.2022<p>Дата проставления: 15.10.2022" data-original-title="" title="">4</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 04.10.2022<p>Дата проставления: 15.10.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 18.10.2022<p>Дата проставления: 31.10.2022" data-original-title="" title="">2</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 25.10.2022<p>Дата проставления: 31.10.2022" data-original-title="" title="">3</span>
                    </td>
                    <td class="grades-average mark4">4,2</td>
                    <td class="grades-marks">
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 08.11.2022<p>Дата проставления: 13.11.2022" data-original-title="" title="">4</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 29.11.2022<p>Дата проставления: 01.12.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 06.12.2022<p>Дата проставления: 16.12.2022" data-original-title="" title="">4</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 13.12.2022<p>Дата проставления: 16.12.2022" data-original-title="" title="">4</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 20.12.2022<p>Дата проставления: 20.12.2022" data-original-title="" title="">4</span>
                    </td>
                    <td class="grades-average mark5">5</td>
                    <td class="grades-marks">
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 17.01.2023<p>Дата проставления: 21.01.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 24.01.2023<p>Дата проставления: 31.01.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 31.01.2023<p>Дата проставления: 31.01.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 14.02.2023<p>Дата проставления: 28.02.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 21.02.2023<p>Дата проставления: 28.02.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 28.02.2023<p>Дата проставления: 05.06.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 07.03.2023<p>Дата проставления: 05.06.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 14.03.2023<p>Дата проставления: 05.06.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 21.03.2023<p>Дата проставления: 05.06.2023" data-original-title="" title="">5</span>
                    </td>
                    <td class="grades-average mark2">2,71</td>
                    <td class="grades-marks">
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 04.04.2023<p>Дата проставления: 25.05.2023" data-original-title="" title="">2</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 11.04.2023<p>Дата проставления: 25.05.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 18.04.2023<p>Дата проставления: 25.05.2023" data-original-title="" title="">2</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 25.04.2023<p>Дата проставления: 25.05.2023" data-original-title="" title="">2</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 02.05.2023<p>Дата проставления: 25.05.2023" data-original-title="" title="">3</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 16.05.2023<p>Дата проставления: 25.05.2023" data-original-title="" title="">3</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 23.05.2023<p>Дата проставления: 27.10.2022" data-original-title="" title="">2</span>
                    </td>
                </tr>
                <tr lesson="3">
                    <td class="grades-lesson-number">3</td>
                    <td class="grades-lesson">Дезинформатика</td>
                    <td class="grades-average mark5">4,92</td>
                    <td class="grades-marks">
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 06.09.2022<p>Дата проставления: 06.10.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 08.09.2022<p>Дата проставления: 06.10.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 13.09.2022<p>Дата проставления: 06.10.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 15.09.2022<p>Дата проставления: 06.10.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 20.09.2022<p>Дата проставления: 06.10.2022" data-original-title="" title="">4</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 22.09.2022<p>Дата проставления: 06.10.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 27.09.2022<p>Дата проставления: 06.10.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 29.09.2022<p>Дата проставления: 06.10.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 04.10.2022<p>Дата проставления: 06.10.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 06.10.2022<p>Дата проставления: 06.10.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 13.10.2022<p>Дата проставления: 13.10.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 18.10.2022<p>Дата проставления: 27.10.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 20.10.2022<p>Дата проставления: 27.10.2022" data-original-title="" title="">5</span>
                    </td>
                    <td class="grades-average mark5">4,82</td>
                    <td class="grades-marks">
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 08.11.2022<p>Дата проставления: 13.11.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 10.11.2022<p>Дата проставления: 10.11.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 17.11.2022<p>Дата проставления: 17.11.2022" data-original-title="" title="">4</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 24.11.2022<p>Дата проставления: 29.11.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 29.11.2022<p>Дата проставления: 29.11.2022" data-original-title="" title="">4</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 01.12.2022<p>Дата проставления: 01.12.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 06.12.2022<p>Дата проставления: 08.12.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 08.12.2022<p>Дата проставления: 08.12.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 13.12.2022<p>Дата проставления: 25.12.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 15.12.2022<p>Дата проставления: 20.12.2022" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 20.12.2022<p>Дата проставления: 20.12.2022" data-original-title="" title="">5</span>
                    </td>
                    <td class="grades-average mark5">4,92</td>
                    <td class="grades-marks">
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 19.01.2023<p>Дата проставления: 19.01.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 24.01.2023<p>Дата проставления: 24.01.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 26.01.2023<p>Дата проставления: 02.02.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 31.01.2023<p>Дата проставления: 31.01.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 02.02.2023<p>Дата проставления: 02.02.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 09.02.2023<p>Дата проставления: 09.02.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 14.02.2023<p>Дата проставления: 14.02.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 16.02.2023<p>Дата проставления: 18.02.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 21.02.2023<p>Дата проставления: 21.02.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 28.02.2023<p>Дата проставления: 28.02.2023" data-original-title="" title="">4</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 09.03.2023<p>Дата проставления: 09.03.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 16.03.2023<p>Дата проставления: 21.03.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 21.03.2023<p>Дата проставления: 21.03.2023" data-original-title="" title="">5</span>
                    </td>
                    <td class="grades-average mark5">5</td>
                    <td class="grades-marks">
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 04.04.2023<p>Дата проставления: 12.04.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 06.04.2023<p>Дата проставления: 12.04.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 11.04.2023<p>Дата проставления: 12.04.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 13.04.2023<p>Дата проставления: 18.04.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 25.04.2023<p>Дата проставления: 25.04.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 27.04.2023<p>Дата проставления: 11.05.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 02.05.2023<p>Дата проставления: 11.05.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 04.05.2023<p>Дата проставления: 11.05.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 11.05.2023<p>Дата проставления: 18.05.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 16.05.2023<p>Дата проставления: 18.05.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 18.05.2023<p>Дата проставления: 18.05.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 23.05.2023<p>Дата проставления: 13.06.2023" data-original-title="" title="">5</span>
                        <span class="mark-span" data-html="true" data-popover-content="Дата урока: 25.05.2023<p>Дата проставления: 13.06.2023" data-original-title="" title="">5</span>
                    </td>
                </tr>















                </tbody>
            </table>
            <table class="table table-bordered GradesTable MobileGrades">

                <thead>
                <tr>
                    <th colspan="3">Эльфийский язык как государственный язык Лесного Королевства</th>
                </tr>
                </thead>
                <tbody period="1">
                <tr>

                    <td class="grades-period-name">1 чет.</td>
                    <td>
                        <span>2</span>

                        <span>2</span>
                    </td>
                    <td class="grades-average mark2">2</td>
                </tr>
                <tr>

                    <td class="grades-period-name">2 чет.</td>
                    <td>
                        <span>3</span>
                        <span>3</span>
                        <span>3</span>

                    </td>
                    <td class="grades-average mark3">3</td>
                </tr>
                <tr>

                    <td class="grades-period-name">3 чет.</td>
                    <td>
                        <span>4</span>
                        <span>4</span>
                        <span>4</span>
                        <span>4</span>

                    </td>
                    <td class="grades-average mark4">4</td>
                </tr>
                <tr>

                    <td class="grades-period-name">4 чет.</td>
                    <td>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>

                    </td>
                    <td class="grades-average mark5">5</td>
                </tr>
                </tbody>
                <thead>
                <tr>
                    <th colspan="5">Алхимия</th>
                </tr>
                </thead>






                <tbody period="2">
                <tr>

                    <td class="grades-period-name">1 чет.</td>
                    <td>
                        <span>3</span>
                        <span>3</span>
                        <span>4</span>
                        <span>5</span>
                        <span>2</span>
                        <span>3</span>
                    </td>
                    <td class="grades-average mark3">3,33</td>
                </tr>
                <tr>

                    <td class="grades-period-name">2 чет.</td>
                    <td>
                        <span>4</span>
                        <span>5</span>
                        <span>4</span>
                        <span>4</span>
                        <span>4</span>
                    </td>
                    <td class="grades-average mark4">4,2</td>
                </tr>
                <tr>

                    <td class="grades-period-name">3 чет.</td>
                    <td>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                    </td>
                    <td class="grades-average mark5">5</td>
                </tr>
                <tr>

                    <td class="grades-period-name">4 чет.</td>
                    <td>
                        <span>2</span>
                        <span>5</span>
                        <span>2</span>
                        <span>2</span>
                        <span>3</span>
                        <span>3</span>
                        <span>2</span>
                    </td>
                    <td class="grades-average mark2">2,71</td>
                </tr>
                </tbody>
                <thead>
                <tr>
                    <th colspan="3">Дезинформатика</th>
                </tr>
                </thead>
                <tbody period="3">
                <tr>

                    <td class="grades-period-name">1 чет.</td>
                    <td>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>4</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                    </td>
                    <td class="grades-average mark5">4,92</td>
                </tr>
                <tr>

                    <td class="grades-period-name">2 чет.</td>
                    <td>
                        <span>5</span>
                        <span>5</span>
                        <span>4</span>
                        <span>5</span>
                        <span>4</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                    </td>
                    <td class="grades-average mark5">4,82</td>
                </tr>
                <tr>

                    <td class="grades-period-name">3 чет.</td>
                    <td>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>4</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                    </td>
                    <td class="grades-average mark5">4,92</td>
                </tr>
                <tr>

                    <td class="grades-period-name">4 чет.</td>
                    <td>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                        <span>5</span>
                    </td>
                    <td class="grades-average mark5">5</td>
                </tr>
                </tbody>






























            </table>
        </div>
        <script>
            $(document).ready(function () {
                if (localStorage.getItem('diary_dark_theme_0000000') == 'true') {
                    $('.diary__theme').find('.fa').removeClass('fa-moon-o').addClass('fa-sun-o');
                }
                $('.navigation__years__department').text($('.navigation__years_selected').text());

                $('.GradesTable .mark-span, .GradesTable .grades-marks i').each(function () {
                    $(this).popover({
                        content: $(this).data('popover-content'),
                        trigger: 'hover',
                        delay: 0,
                        html: true,
                        placement: 'bottom'
                    });
                });
                $('.navigation [data-popover-content]').each(function () {
                    $(this).popover({
                        content: $(this).data('popover-content'),
                        container: $('.navigation'),
                        trigger: 'hover',
                        delay: 0,
                        html: true,
                        placement: 'bottom'
                    });
                });
            });

            $('.navigation__years .dropdown-item').on('click', function () {
                waitingDialog.show();
                location.href = '/users/diaries/grades'
                    + '?rooId=00'
                    + '&instituteId=' + $(this).attr('model-institute-id')
                    + '&departmentId=' + $(this).attr('model-department-id')
                    + '&pupilId=0000000';
            });

            $('.diary__theme').on('click', function () {
                $('.diary__theme').find('.fa').toggleClass('fa-sun-o').toggleClass('fa-moon-o');
                if ($('.diary__theme .fa-sun-o').length) {
                    switch_theme('dark');
                    localStorage.setItem('diary_dark_theme_0000000', 'true');
                } else {
                    switch_theme('default');
                    localStorage.setItem('diary_dark_theme_0000000', 'false');
                }
            });
        </script>
    </main>

    <aside class="system-message">
        <div class="system-message-wrapper">
        </div>
    </aside>

    <footer class="position-relative">
        <div class="container-def border-top py-3">

            <div class="row">
                <div class="col-lg-6 col-12">
                    <h5>Ресурсы</h5>
                    <div class="d-flex flex-sm-row flex-column">
                        <ul class="list-unstyled mr-3 mb-0 mb-sm-3">
                            <li><a href="https://glavarb.ru/" target="_blank">Глава Республики Башкортостан</a></li>
                            <li><a href="https://www.pravitelstvorb.ru/" target="_blank">Правительство Республики Башкортостан</a></li>
                            <li><a href="https://edu.gov.ru/" target="_blank">Министерство просвещения Российской Федерации</a></li>
                            <li><a href="https://minobrnauki.gov.ru/" target="_blank">Министерство науки и высшего образования Российской Федерации</a></li>
                            <li><a href="https://education.bashkortostan.ru/" target="_blank">Министерство образования и науки Республики Башкортостан</a></li>
                        </ul>
                        <ul class="list-unstyled">
                            <li><a href="https://www.bashkortostan.ru/" target="_blank">Портал Республики Башкортостан</a></li>
                            <li><a href="https://obrnadzorrb.bashkortostan.ru/" target="_blank">Управление по контролю и надзору в сфере образования РБ</a></li>
                            <li><a href="https://www.gosuslugi.ru/" target="_blank">Электронное правительство</a></li>
                            <li>Телефон доверия для детей, подростков, родителей – <a href="tel:88002000122" target="_blank">8-800-2000-122</a></li>
                        </ul>
                    </div>

                </div>
                <div class="col-sm-6 col-lg-3 col-12">
                    <h5>Документация</h5>
                    <ul class="list-unstyled">
                        <li><a href="/Home/FooterDocuments" target="_blank">Нормативные документы</a></li>
                        <li><a href="/Home/FooterInstructions" target="_blank">Инструкции</a></li>
                        <li><a href="/Home/FooterMemo" target="_blank">Памятка для родителей</a></li>
                    </ul>
                </div>
                <div class="col-sm-6 col-lg-3 col-12">
                    <h5>Поддержка</h5>
                    <ul class="list-unstyled">
                        <li><a href="mailto:edu@brsc.ru">HelpDesk</a></li>
                        <li>E-mail: edu@brsc.ru</li>
                        <li>Горячая линия: 8-800-100-81-80</li>
                        <li class="pt-3 text-muted">При обращении в службу поддержки просьба указывать ФИО, школу, класс</li>
                    </ul>

                </div>


            </div>

        </div>
        <div class="container-fluid" style="background-color: #eee;">
            <div class="row p-3 position-relative" style="overflow: hidden;">
                <div class="copyright col-12 d-flex justify-content-end">
                    <p class="mb-0 text-center">©&nbsp;Электронная школа «ELSCHOOL», 2024 Версия: 2.5.8794.31649</p>
                </div>
            </div>
        </div>
    </footer>






    <div class="offline-ui offline-ui-up"><div class="offline-ui-content"></div><a href="" class="offline-ui-retry"></a></div></body></html>)";
}