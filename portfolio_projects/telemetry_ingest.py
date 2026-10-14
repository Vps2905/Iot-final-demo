"""Import demo/serial JSON telemetry into SQLite. No outbound network requests."""
import argparse,json,sqlite3,sys
from pathlib import Path
if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--input',type=Path,default=Path(__file__).parent/'sample_telemetry.jsonl');p.add_argument('--serial');p.add_argument('--database',type=Path,default=Path('telemetry.sqlite'));a=p.parse_args()
    connection=sqlite3.connect(a.database);connection.execute('CREATE TABLE IF NOT EXISTS telemetry(id INTEGER PRIMARY KEY,payload TEXT NOT NULL)')
    if a.serial:
        import serial
        stream=serial.Serial(a.serial,115200,timeout=2)
    else:stream=a.input.open()
    try:
        for line in stream:
            if not line:continue
            try:
                row=json.loads(line)
                if not isinstance(row,dict) or row.get('device') not in {'bin-demo','solar-cleaner-demo'}:raise ValueError('Unrecognized telemetry')
                connection.execute('INSERT INTO telemetry(payload) VALUES (?)',(json.dumps(row),));connection.commit();print(json.dumps(row))
            except (ValueError,TypeError,json.JSONDecodeError) as e:print('Skipped invalid telemetry:',e,file=sys.stderr)
    except KeyboardInterrupt:pass
    finally:stream.close();connection.close()
