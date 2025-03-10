
{% if audience == "internal" %}

#### **Q: Как получить вычислительную или дисковую квоту в {{product-name}}?**

**A:** Для получения новой квоты или расширения одной из текущих необходимо заполнить форму. Ссылки на формы для различных случаев приведены в разделе [Запрос и получение ресурсов](../../../user-guide/storage/quota-request.md).

------

{% endif %}


#### **Q: Как добавить колонку в таблицу {{product-name}}?**

**A:** Необходимо получить текущую схему таблицы:

`yt get //home/maps-nmaps/production/pedestrian/address_tasks/@schema --format '<format=text>yson'`

И заменить схему на новую:
```bash
yt alter-table //home/maps-nmaps/testing/pedestrian/address_tasks --schema '<"unique_keys"=%false;"strict"=%true;>[{"name"="timestamp";"required"=%false;"type"="uint64";"sort_order"="ascending";};{"name"="lon";"required"=%false;"type"="double";};{"name"="lat";"required"=%false;"type"="double";};{"name"="buildingId";"required"=%false;"type"="string";};{"name"="taskId";"required"=%false;"type"="string";};{"name"="pedestrianType";"required"=%false;"type"="string";};{"name"="buildingPerimeter";"required"=%false;"type"="double";};{"name"="buildingShape";"required"=%false;"type"="string";};]'
```

В YQL можно использовать выражение `UNION ALL` для объединения новых данных с новой колонкой и старых данных из таблицы.

------
#### **Q: Получаю ошибку при попытке изменить схему таблицы - Changing «strict» from «false» to «true» is not allowed. Что делать?**

**A:** Нельзя поменять схему у непустой таблицы со слабой на строгую, так как для валидации подобного действия необходимо прочитать всю таблицу, чтобы убедиться, что данные соответствуют новой схеме. Проще всего создать новую таблицу и перезаписать данные из старой через read + write или запустив операцию [Merge](../../../user-guide/data-processing/operations/merge.md).

------
#### **Q: Как авторизоваться при работе с YT из консоли?**

**A:** Необходимо сохранить токен нужного пользователя в файл `~/.yt/token`.

------
#### **Q: Можно ли уменьшить коэффициент репликации у временных таблиц в native C++ wrapper?**

**A:** Нет, в wrapper такая возможность не предусмотрена.

------
#### **Q: При использовании python wrapper возникает ошибка «ImportError: Bad magic number in ./modules/yt/__init__.pyc». Что делать?**

**A:** Такая ошибка возникает при несоответствии версии python у клиента, где запускается скрипт, и на кластере. Используйте для запуска ту же версию python, что и на кластере. Определить текущую версию можно так:

```bash
yt vanilla --tasks '{master = {job_count = 1; command = "python --version >&2"}}'
Python 2.7.3
```

Версия python может отличаться на разных узлах кластера. Надёжнее всего использовать свой [образ ФС](../../../user-guide/data-processing/porto/layer-paths.md) для запуска джобов.

------
#### **Q: Каковы накладные расходы при чтении небольших диапазонов в таблицах и при чтении небольших таблиц?**

**A:** Небольшие диапазоны не создают накладных расходов, с диска читаются только релевантные блоки. При этом все чтения статических таблиц требуют запроса метаданных на мастер-сервере. Общение с мастер-сервером в данном случае является узким местом. В этом случае стоит читать статические таблицы меньшим числом запросов (более крупными частями), минимизировать нагрузку на мастер-сервер. Или перестроить свой процесс и читать из динамических таблиц.

------
#### **Q: Можно ли эффективно организовать хранение байтовых чисел (hex) в ключах вместо строк?**

**A:** Можно при использовании формата [YSON](../../../user-guide/storage/formats.md#yson) или [JSON](../../../user-guide/storage/formats.md#json).

------
#### **Q: Каковы уровни логирования в консольном клиенте и как они задаются?**

**A:** Уровни логирования в консольном клиенте задаются через переменную окружения `YT_LOG_LEVEL`, по умолчанию принято значение `INFO`. Изменить уровень логирования можно командой `export YT_LOG_LEVEL=WARNING`. Доступны следующие уровни логирования:

- `INFO` — выводится прогресс выполнения операции и другая полезная информация;
- `WARNING` — выводятся предупреждения. Например, не удалось выполнить запрос, и он отправляется повторно, или входная таблица операции пуста. Подобные ошибки не критичны, и клиент может продолжать успешно работать;
- `ERROR` — все ошибки, после которых клиент не может продолжить работу. Подобные ошибки приводят к исключению (Exception). Исключение обрабатывается, после чего клиент аварийно завершает работу с ненулевым кодом возврата.

------
#### **Q: Как устроена очистка временных данных на кластерах?**

**A:** На большинстве кластеров {{product-name}} регулярно — раз в день или чаще — запускается скрипт очистки `//tmp`, который находит и удаляет давно не используемые или расходующие определенную часть квоты аккаунта tmp данные. Подробное описание процесса очистки содержится в разделе Системные процессы. Пользователям необходимо учитывать наличие регулярной очистки при записи данных в `//tmp`.

------
#### **Q: При чтении с помощью команды read небольшой таблицы клиент повисает при перезапросах. В чем может быть дело?**

**A:** Одна из возможных частых причин — слишком большое число (мелких) чанков в таблице. Следует запустить операцию [Merge](../../../user-guide/data-processing/operations/merge.md), указав опцию `--spec '{force_transform=true}'`. При появлении таких таблиц в результате работы операций консольный клиент выдает предупреждение, содержащее, помимо прочего, команду, которую можно выполнить для укрупнения чанков таблицы. Также можно указать опцию `auto_merge_output={action=merge}`, в этом случае слияние будет выполняться автоматически.

------
#### **Q: Операция завершилась с ошибкой «Account "tmp" is over disk space (или chunk) limit», в чем дело?**

**A:** На кластере закончилось место для хранения временных данных (аккаунт tmp), либо чанков в этом аккаунте стало слишком много. К данному аккаунту имеют доступ все пользователи кластера, так что возможно его переполнение. Данное обстоятельство необходимо учитывать и, если переполнение квоты tmp критично для ваших процессов, то для временных данных следует использовать другую директорию в собственном аккаунте. Некоторые API используют `//tmp` как путь по умолчанию для хранения различных временных данных. В этом случае следует перенастроить их, чтобы использовались поддиректории внутри директории вашего проекта.

------
#### **Q: Операция упала с ошибкой «Account "intermediate" is over disk space (или chunk) limit», в чем дело?**

**A:** На кластере закончилось место для хранения промежуточных данных операций (аккаунт `intermediate`), либо чанков в этом аккаунте стало слишком много.
Если вы не указывали `intermediate_data_account` (смотрите раздел [Настройки операций](../../../user-guide/data-processing/operations/operations-options.md), [Sort](../../../user-guide/data-processing/operations/sort.md), [MapReduce](../../../user-guide/data-processing/operations/mapreduce.md)). Это значит, что вы делите данный аккаунт со всеми. Чтобы избежать этой проблемы, укажите `intermediate_data_account`.

------
#### **Q: Является ли чтение таблицы (или файла) в {{product-name}} консистентной операцией? Что будет, если читать таблицу и одновременно с этим её удалить?**

**A:** С одной стороны, является, то есть если операция чтения завершится успешно, то будут прочитаны ровно те данные, которые были в таблице или файле в момент запуска операции. С другой стороны, чтение может оборваться, если таблицу в это время удалить. Чтобы избежать последнего, необходимо создать транзакцию и взять в ней snapshot-lock на таблицу или файл. При использовании python API, в том числе python CLI и включенных retry при чтении, данная блокировка берется автоматически.

------
#### **Q: При запуске клиента получаю ошибку "Cannot determine backend type: either driver config or proxy url should be specified". Что делать?**

**A:** Проверьте, указана ли переменная окружения `YT_PROXY=<cluster-name>`.

------

#### **Q: Что делать, если запрос Python обёртки падает с "gaierror(-2, 'Name or service not known')"?**

**A:** Если возникла ошибка вида:
`has failed with error <class 'yt.packages.requests.exceptions.ConnectionError'>, message: '('Connection aborted.', gaierror(-2, 'Name or service not known'))'`,
Ошибка «Name or service not known» - это ошибка DNS, сообщающая о том, что запрошенная DNS запись не была найдена.
В контексте {{product-name}} и надежно работающего DNS, это означает, что, скорее всего, ваш сервис пытается разрезолвить A запись для какого-то из хостов {{product-name}}, но {{product-name}} является ipv6 only сервисом, потому ничего не получится. Ваш сервис должен корректно работать с ipv6 сетью. Кроме того, возможно выставлена переменная окружения `YT_FORCE_IPV4`, которая переключает yt.wrapper в ipv4 only режим. Ее нужно убрать.
Чтобы посмотреть переменные окружения {{product-name}}, нужно выполнить в терминале:
`env | grep YT_`
Для того, чтобы убрать переменную `YT_FORCE_IPV4` из окружения:
`unset YT_FORCE_IPV4`

------
#### **Q: Что делать, если возникает ошибка «Account "..." is over disk space limit (node count limit, etc)»?**

**A:** Сообщение говорит о том, что переполнилась одна из квот аккаунта. В системе действуют квоты на ресурсы различных видов. Подробнее о видах квот, а также формы для их изменения читайте в разделе [Квоты](../../../user-guide/storage/quotas.md).

------
#### **Q: Как найти, кто занимает место в аккаунте или все ноды с определенным аккаунтом?**

**A:** Короткий ответ: `yt find / --name "*" --account <account_name>`

Более подробный ответ:
1. Посмотрите в корзину (`//tmp/trash/by-account/<account_name>`). Для этого стоит перейти по указанному пути в разделе **Navigation** в веб-интерфейсе;
2. Поищите с помощью `yt find` таблицы под вашим аккаунтом в `//tmp` и связных с вами проектных директориях. Обратите внимание, что `yt find` не заходит в директории, в которые у вас нет доступа;
3. Обратитесь к администратору системы.
{% if audience == "internal" %}
4. Данные могут быть удалены из Кипариса, но использоваться выполняющимися операциями. Такие операции можно поискать с помощью скрипта [find_top_operations](https://a.yandex-team.ru/arc/trunk/arcadia/yt/yt/scripts/find_top_operations), например так: `./find_top_operations --proxy hahn --in-account dev`
{% endif %}

------
#### **Q: Как изменить аккаунт таблицы?**

**A:** `yt set //path/to/table/@account my-account`

------
#### **Q: Как узнать, сколько ресурсов занимает директория, включая все содержащиеся в ней таблицы, файлы и т. д.?**

**A:** `yt get //path/to/dir/@recursive_resource_usage` или выбрать **Show all resources** в разделе **Navigation** в веб-интерфейсе.

------
#### **Q: При работе с системой возникла ошибка «Transaction has expired or was aborted». Что она означает и как с ней бороться?**

**A:** При создании мастер-транзакции указывается **таймаут**, и пользователь обязуется посылать пинги транзакции не реже раза в указанный промежуток времени. Если с момента создания или последнего пинга проходит время, превышающее таймаут, система прерывает транзакцию.  Причины такого поведения могут быть следующие:

1. Проблемы сетевого взаимодействия между клиентской машиной и кластером;
2. Некорректная работа клиента — отсутствие отправки пингов. Пинги либо не отправляются по коду, либо код, выполняющий такую отправку, не вызывается. Например, в случае использования python такое может случиться, если в программе на долгое время происходит взятие GIL-блокировки при работе с какими-либо нативными библиотеками;
3. Ведутся работы на кластере;
4. Имеются известные проблемы доступности;
5. Транзакция была явно прервана клиентом, в чём можно убедиться, изучив логи сервера.

В остальных случаях для изучения проблемы необходимы клиентские debug-логи. На серверной стороне лишь известно, что пингов нет, поэтому следует обязательно включить debug-логирование и собрать debug logs. Например, выставив переменную `YT_LOG_LEVEL=debug`, что подходит для большинства поддерживаемых API.

-----
#### **Q: На странице операции появилось сообщение «"owners" field in spec ignored as it was specified simultaneously with "acl"». Что это значит?** { #ownersinspecignored }

**A:** Сообщение означает, что в спецификации операции указаны одновременно устаревшее поле «owners» и поле «acl», при этом приоритет отдан последнему, то есть поле «owners» было проигнорировано.

------
#### **Q: Как можно автоматически ротировать узлы, удалять старше определенного времени?**

**A:** Следует воспользоваться атрибутом `expiration_time`. Подробнее можно прочитать в разделе [Дерево метаинформации](../../../user-guide/storage/cypress.md#TTL).

------
#### **Q: Как можно автоматически удалять узлы, которыми не пользовались дольше определенного времени?**

**A:** Следует воспользоваться атрибутом `expiration_timeout`. Подробнее можно прочитать в разделе [Дерево метаинформации](../../../user-guide/storage/cypress.md#TTL).

------
#### **Q: В ходе работы операции появилось предупреждение «Detected excessive disk IO in <job_type> jobs. IO throttling was activated». Что это значит?** { #excessivediskusage }

**A:** Джобы операции совершают много операций ввода/вывода с локальным диском. Чтобы минимизировать негативные последствия такого поведения для кластера, джобы были ограничены через механизм [троттлинга blkio cgroup](https://www.kernel.org/doc/Documentation/cgroup-v1/blkio-controller.txt). О возможных причинах подобного поведения в примерах раздела [Статистики джобов](../../../user-guide/problems/jobstatistics.md#excessive_io).


------
#### **Q: Какие пути веб-интерфейс исправляет автоматически при включённой настройке Enable path autocorrection?** { #enablepathautocorrection }

**A:** Веб-интерфейс не сообщает о том, какие ошибки в пути были исправлены.
Например, `//home/user/tables/` — путь такого вида всегда невалидный, при отображении пути в веб-интерфейсе неэкранированный слеш в конце пути будет отброшен.

------
#### **Q: Как понять успешно ли скачалась таблица из веб-интерфейса, а если нет, как посмотреть ошибку?** { #web_interface_table_download }

**A:** При возникновении ошибки она будет записываться в скачиваемый файл. Ошибка может произойти в любой момент во время скачивания — необходимо проверять конец файла. Пример ошибки:

```json
==================================================================" "# "" ""#
{
    "code" = 1;
    "message" = "Missing key column \"key\" in record";
    "attributes" = {
        "fid" = 18446479488923730601u;
        "tid" = 9489286656218008974u;
        "datetime" = "2017-08-30T15:49:38.645508Z";
        "pid" = 864684;
        "host" = "<cluster_name>";
    };
}
==================================================================" "# "" ""#
```

------
#### **Q: Вы пытаетесь локально запустить программу, которая обращается через RPC в {{product-name}}, и получаете ошибку «Domain name not found»**

**A:** В логе также можно встретить `W Dns DNS resolve failed (HostName: your-local-host-name)`. Ошибка возникает при разрешении имени локального хоста, а в глобальном DNS его нет. Дело в том, что {{product-name}} RPC client по умолчанию использует IPv6 и отключает IPv4. Поэтому строка `127.0.1.1  your-local-host-name` в локальном файле `/etc/hosts` не работает. Если дописать в указанный файл `::1  your-local-host-name`, это должно решить проблему.

------
#### **Q: Как скопировать не всю таблицу, а только некоторый диапазон строк?**

**A:** В текущей реализации операция `Copy` не поддерживает копирование диапазонов, но можно воспользоваться командой [Merge](../../../user-guide/data-processing/operations/merge.md), она отработает быстро. При использовании режима `ordered` сохранится сортировка в простых случаях (например, когда диапазон один). Пример команды:

```bash
yt merge --src '_path/to/src/table[#100:#500]' --dst _path/to/dst/table --mode ordered
```

------
#### **Q: Как узнать, кто работает с моими таблицами?**

**A:** Для этого можно проанализировать лог доступа к мастер-серверу.

------
#### **Q: Как восстановить удаленные данные?**

**A:** Если удаление было через UI и там не была выбрана опция `Delete permanently`, то можно поискать таблицы в мусорке в папке соответствующего аккаунта.
Если удаление было через `yt remove` или аналогичные вызовы API, то восстановление **невозможно**.

------
#### **Q: Ошибка «Operations of type "remote-copy" must have small enough specified resource limits in some of ancestor pools»**

**A:** Операции [RemoteCopy](../../../user-guide/data-processing/operations/remote-copy.md) создают нагрузку на cross-DC сеть.
Для ограничения нагрузки было введено искусственное ограничение: операции RemoteCopy должны запускаться в пуле с лимитом на `user_slots`. Лимит указан в тексте ошибки и чаще всего равен `2000`.

Если в пуле планируется запускать только RemoteCopy, то достаточно выставить это ограничение для пула
`yt set //sys/pools/..../your_pool/@resource_limits '{user_slots=2000}'`.

{% if audience == "internal" %}

Более подробно: https://ignat.at.yandex-team.ru/326/

------
#### **Q: Не создался пользователь на кластере для робота. Токен при этом получить смогли.**

**A:** Для того, чтобы роботный пользователь появился на кластере необходимо запросить через [IDM](https://idm.yandex-team.ru/) доступ роботу в одну из групп в соответствующей системе [IDM](https://idm.yandex-team.ru/systems#sort-by=name,f-system-status=active). Подробнее про токены можно прочесть в разделе [Как попробовать](../../../quickstart.md#how-to-get-oauth-token).

------
#### **Q: Можно ли выдать доступ через {{product-name}} ACL на ABC-сервис?**

**A:** В {{product-name}} ACL указываются либо пользователи {{product-name}}, либо группы {{product-name}}. Тем самым, задача сводится к тому, чтобы узнать, есть ли в {{product-name}} группа, отвечающая заданному ABC-сервису, и как она называется. Проще всего дать ответ, если где-либо в IDM на данный сервис выдана хотя бы одна роль в {{product-name}}, например на чтение или запись в каталог. В таком случае следует пойти в {{product-name}} UI на вкладку ACL каталога и найти там соответствующую строчку. В ней имя группы будет иметь вид `idm-group:N`, где N -- некоторое число (внутренний идентификатор IDM). Именно эту строчку и нужно указывать во всех ACL, где требуется выдать доступ на ABC-сервис. Если же на сервис покуда не выдано ни одной роли в {{product-name}}, то можно проделать следующий обходной маневр: выдать такую роль на любой каталог, затем проанализировать его ACL (как указано выше), а затем отозвать роль. Вознишкая при этом {{product-name}}-группа с именем `idm-group:N` пожизненно будет синхронизироваться с IDM и ABC.

------
#### **Q: При запуске операции из python wrapper от роботного пользователя получаю ошибку "permission for node //tmp/yt_wrapper/file_storage is not allowed by any matching ACE"**

**A:** У робота нет доступа к `/tmp`, необходимо запросить для робота роль **group member yandex**  через [IDM](https://idm.yandex-team.ru/). Подробнее можно узнать в разделе [Аутентификация](../../../user-guide/storage/auth.md#getting_token_for_robot).


#### **Q: Как узнать, валиден ли токен, от какого он пользователя и принимает ли его конкретный кластер?**

**A:** К примеру, если вы получили ошибку аутентификации:
`Your authentication token was rejected by the server (X-YT-Request-ID: 6e101e7733a31832). Please refer to http:<cluster_fqdn>/auth/ for obtaining a valid token`, следует отправить HTTP-запрос с токеном в вызов /auth:

`curl -H 'Authorization: OAuth ${TOKEN}' http://<cluster_fqdn>/auth/whoami`

{% endif %}
