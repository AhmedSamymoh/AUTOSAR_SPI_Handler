#!/bin/bash

# ######## Set your Jira credentials and endpoint ######## 
JIRA_USER="ahmeds.elnozahy@gmail.com"
JIRA_API_TOKEN="ATATT3xFfGF0xYT7HPCi5lokFfZWNkl0R2xi9BpiieoCRoG3Dn64p5PHPNO-J0-xpcxCZ2GgfV36TfLYSqwT0fQddokHukUVKaxaTqEvQiDM9zbsr2u4ME8Nlp8cTwIvw93CRaD6_U1Awmr3pQFAgIsli5clBlZoRsollYlRztAtrIQ-qDiyUg4=D46B4967"
JIRA_URL="https://ahmedselnozahy.atlassian.net/rest/api/2/search?jql=project=CCB"

# ######## Output file ######## 
OUTPUT_FILE="jira_all_issues.csv"

# ######## Make API request and save the response to a file ######## 
curl -u "$JIRA_USER:$JIRA_API_TOKEN" -X GET -H "Content-Type: application/json" "$JIRA_URL" -o response.json

# Check if the response contains an error
if jq -e .errors response.json > /dev/null 2>&1; then
    echo "Error in response"
    cat response.json
    exit 1
fi

# Process the JSON response to extract the data and save it as CSV
{
    echo "KEY,SPRINT,SUMMARY,ASSIGNEE,STATUS,START DATE,UPDATED"
    jq -r '.issues[] | [.key, (.fields.customfield_10020[0].name // "N/A"), .fields.summary, (.fields.assignee.displayName // "Unassigned"), .fields.status.name, .fields.created, .fields.updated] | @csv' response.json
} > "$OUTPUT_FILE"

# ######## Clean up ######## 
rm response.json

echo "CSV file has been saved to $OUTPUT_FILE"

# ######## Run the Python script ######## 
echo "Running HighestSprint.py!"
python3 HighestSprint.py
